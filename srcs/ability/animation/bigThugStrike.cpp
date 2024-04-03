
#include "../../../hdr/global.h"
#define TIME_DONE 200

static Vector GetDirection(Character *character, Character *target)
{
	SDL_Point cPos = character->position;
	SDL_Point tPos = target->position;
	SDL_Rect cDest = gameState.battle.ground->getTileDest(cPos);
	SDL_Rect tDest = gameState.battle.ground->getTileDest(tPos);
	Vector ret((float)(tDest.x - cDest.x), (float)(tDest.y - cDest.y));
	return (ret);
}

BigThugStrike::BigThugStrike(Character *character, Character *target)
{
	BigThugStrike::character = character;
	BigThugStrike::target = target;
	character->setAnimationActive(true);
	Vector dir = GetDirection(character, target).Normalized();
	character->sprite->setTexture(gameState.textures.chars.bigThugIdle[0]);
	character->setAnimationActive(true);
	if (dir.y > 0.0f)
		orderDiff = 1;
	character->sprite->orderLayer += orderDiff;
	mover = new SpriteMover(character->sprite, dir, 36, 100.0f);
	destDims = {character->sprite->dest.w, character->sprite->dest.h};
}

void BigThugStrike::CreateTrail()
{
	character->sprite->dest = {character->sprite->dest.x - 1500, character->sprite->dest.y + 200, 9700, 7060};
	character->sprite->setTexture(gameState.textures.attacks.bigThugAttack[0]);
	trail = new Sprite(gameState.textures.attacks.bigThugAttack[1], character->sprite->dest, NULL, NULL, 0, FLIP_NONE);
	trail->orderLayer = character->sprite->orderLayer;
	trail->z = character->sprite->z - 0.05f;
	gameState.render->AddSprite(trail, BATTLEGROUND_LAYER);
}

void BigThugStrike::UpdateTrail(int ret)
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

void BigThugStrike::Update()
{
	createDamage = false;
	if (done)
		return ;
	int ret = mover->Update();
	UpdateTrail(ret);
	if (ret == 5)
	{
		PlaySound(gameState.audio.bigThugStrike, Channels::VOLUME_26, 0);
		CreateTrail();
	}
	if (ret == 10)
		createDamage = true;
	if (ret == 28)
	{
		character->sprite->orderLayer -= orderDiff;
		character->sprite->dest = {character->sprite->dest.x + 1500, character->sprite->dest.y - 200, destDims.x, destDims.y};
		character->sprite->setTexture(gameState.textures.chars.bigThugIdle[0]);
	}
	if (ret == (-1))
	{
		done = true;
		return ;
	}
	counter++;
	if (counter > TIME_DONE)
		done = true;
}

void BigThugStrike::Destroy()
{
	character->setAnimationActive(false);
	if (mover != NULL)
		delete mover;
	if (trail != NULL)
		delete trail;
}
