
#include "../../../hdr/global.h"
#define TIME 200

static Vector GetDirection(Character *character, Character *target)
{
	SDL_Point cPos = character->position;
	SDL_Point tPos = target->position;
	SDL_Rect cDest = gameState.battle.ground->getTileDest(cPos);
	SDL_Rect tDest = gameState.battle.ground->getTileDest(tPos);
	Vector ret((float)(tDest.x - cDest.x), (float)(tDest.y - cDest.y));
	return (ret);
}

ShieldBash::ShieldBash(Character *character, Character *target)
{
	ShieldBash::character = character;
	ShieldBash::target = target;
	character->setAnimationActive(true);
	character->sprite->setTexture(gameState.textures.chars.knightIdle[0]);
	Vector dir = GetDirection(character, target).Normalized();
	trail = NULL;
	if (dir.y > 0.0f)
		orderDiff = 1;
	character->sprite->orderLayer += orderDiff;
	mover = new SpriteMover(character->sprite, dir, 36, 100.0f);
	dims = {character->sprite->dest.w, character->sprite->dest.h};
}

void ShieldBash::CreateTrail()
{
	SDL_Rect dest = {character->sprite->dest.x + 500, character->sprite->dest.y, 9700, 7060};
	character->sprite->dest = dest;
	character->sprite->setTexture(gameState.textures.attacks.shieldBash[0]);
	trail = new Sprite(gameState.textures.attacks.shieldBash[1], dest, NULL, NULL, 0, FLIP_NONE);
	trail->orderLayer = character->sprite->orderLayer;
	trail->z = character->sprite->z + 0.05f;
	gameState.render->AddSprite(trail, BATTLEGROUND_LAYER);
}

void ShieldBash::UpdateTrail(int ret)
{
	if (trail == NULL)
		return ;
	trail->dest = character->sprite->dest;
	if (ret <= 13)
		return ;
	float unit = 255.0f / 10.0f;
	int count = ret - 13;
	float alpha = 255.0f - (unit * (float)count);
	int used = rounding(alpha);
	if (used <= 0)
	{
		delete trail;
		trail = NULL;
		return ;
	}
	trail->AlphaMod(used);
}

void ShieldBash::Update()
{
	createDamage = false;
	if (done)
		return ;
	int ret = mover->Update();
	UpdateTrail(ret);
	if (ret == 5)
		CreateTrail();
	if (ret == 10)
		createDamage = true;
	if (ret == 28)
	{
		character->sprite->orderLayer -= orderDiff;
		character->sprite->dest = {character->sprite->dest.x - 500, character->sprite->dest.y, dims.x, dims.y};
		character->sprite->setTexture(gameState.textures.chars.knightIdle[0]);
	}
	if (ret == (-1))
	{
		done = true;
		return ;
	}
	counter++;
	if (counter > TIME)
		done = true;
}

void ShieldBash::Destroy()
{
	if (trail != NULL)
		delete trail;
	if (mover != NULL)
		delete mover;
	character->setAnimationActive(false);
}
