
#include "../../../hdr/global.h"

static Vector GetDirection(Character *character, Character *target)
{
	SDL_Point cPos = character->position;
	SDL_Point tPos = target->position;
	SDL_Rect cDest = gameState.battle.ground->getTileDest(cPos);
	SDL_Rect tDest = gameState.battle.ground->getTileDest(tPos);
	Vector ret((float)(tDest.x - cDest.x), (float)(tDest.y - cDest.y));
	return ((ret).Normalized());
}

AxeSlash::AxeSlash(Character *character, Character *target)
{
	PlaySound(gameState.audio.axeSwing, Channels::VOLUME_30, 0);
	AxeSlash::character = character;
	AxeSlash::target = target;
	Vector dir = GetDirection(character, target);
	mover = new CharacterMover(character, dir, 14, 14, 180.0f);
	trail = new Sprite(gameState.textures.attacks.axeSlash[1], character->sprite->dest, NULL, NULL, 0, FLIP_NONE);
	trail->orderLayer = character->sprite->orderLayer;
	trail->z = character->sprite->z - 0.1f;
	character->setAnimationActive(true);
}

void AxeSlash::CreateTrail()
{
	character->sprite->setTexture(gameState.textures.attacks.axeSlash[0]);
	character->sprite->dest.x += 1300;
	character->sprite->dest.y -= 100;
	gameState.render->AddSprite(trail, BATTLEGROUND_LAYER);
	trail->dest = character->sprite->dest;
}

void AxeSlash::FadeTrail(int ret)
{
	if (ret < 12)
		return ;
	float unit = 255.0f / 12.0f;
	float count = (float)ret - 11.0f;
	float alpha = 255.0f - (unit * count);
	int used = rounding(alpha);
	if (used < 0)
		used = 0;
	if (used > 255)
		used = 255;
	trail->AlphaMod(used);
}

void AxeSlash::SetTextBack()
{
	character->sprite->setTexture(gameState.textures.chars.raiderIdle[0]);
	character->sprite->dest.x -= 1300;
	character->sprite->dest.y += 100;
}

void AxeSlash::Update()
{
	createDamage = false;
	if (done)
		return ;
	int ret = mover->Update();
	if (ret == (-1))
	{
		done = true;
		return ;
	}
	if (ret == 4)
		CreateTrail();
	if (ret == 11)
		createDamage = true;
	if (ret == 27)
		SetTextBack();
	FadeTrail(ret);
	trail->dest = character->sprite->dest;
}

void AxeSlash::Destroy()
{
	character->setAnimationActive(false);
	if (trail != NULL)
		delete trail;
	if (mover != NULL)
		delete mover;
}
