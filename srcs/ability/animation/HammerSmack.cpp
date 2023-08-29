
#include "../../../hdr/global.h"

Vector HammerSmack::GetDirection()
{
	SDL_Point cPos = character->position;
	SDL_Point tPos = target->position;
	SDL_Rect cDest = gameState.battle.ground->getTileDest(cPos);
	SDL_Rect tDest = gameState.battle.ground->getTileDest(tPos);
	Vector ret((float)(tDest.x - cDest.x), (float)(tDest.y - cDest.y));
	return ((ret).Normalized());
}

HammerSmack::HammerSmack(Character *character, Character *target)
{
	HammerSmack::character = character;
	HammerSmack::target = target;
	mover = new CharacterMover(character, GetDirection(), 14, 14, 180.0f);
	character->setAnimationActive(true);
	SDL_Rect dest = character->sprite->dest;
	trail = new Sprite(gameState.textures.attacks.hammerSmack[1], dest, NULL, NULL, 0, FLIP_NONE);
	trail->orderLayer = character->sprite->orderLayer;
	trail->z = character->sprite->z - 0.1f;
	trail->Deactivate();
	gameState.render->AddSprite(trail, BATTLEGROUND_LAYER);
}

void HammerSmack::Update()
{
	damage = false;
	if (done)
		return ;
	int ret = mover->Update();
	if (ret == (-1))
	{
		done = true;
		return ;
	}
	if (ret == 4)
	{
		character->sprite->setTexture(gameState.textures.attacks.hammerSmack[0]);
		trail->Activate();
	}
	if (ret >= 5)
	{
		float unit = 255.0f / 18.0f;
		int alpha = rounding(255.0f - (unit * (float)(ret - 5)));
		trail->AlphaMod(alpha);
	}
	if (ret == 22)
	{
		trail->Deactivate();
		character->sprite->setTexture(gameState.textures.chars.smithIdle[0]);
	}
	if (ret == 8)
		damage = true;
	trail->dest = character->sprite->dest;
}

void HammerSmack::Destroy()
{
	delete mover;
	delete trail;
	character->setAnimationActive(false);
}
