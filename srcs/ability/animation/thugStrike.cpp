
#include "../../../hdr/global.h"

static Vector GetDirection(Character *character, Character *target)
{
	SDL_Point cPos = character->position;
	SDL_Point tPos = target->position;
	SDL_Rect cDest = gameState.battle.ground->getTileDest(cPos);
	SDL_Rect tDest = gameState.battle.ground->getTileDest(tPos);
	Vector ret((float)(tDest.x - cDest.x), (float)(tDest.y - cDest.y));
	return (ret);
}

ThugStrike::ThugStrike(Character *character, Character *target)
{
	ThugStrike::character = character;
	Vector dir = GetDirection(character, target).Normalized();
	character->setAnimationActive(true);
	mover = new SpriteMover(character->sprite, dir, 20, 200.0f);
	if (dir.y > 0.0f)
		orderAdd = 1;
	character->sprite->orderLayer += orderAdd;
}

void ThugStrike::Update()
{
	createDamage = false;
	if (done)
		return ;
	int ret = mover->Update();
	if (ret == 4)
		PlaySound(gameState.audio.thugStrike, Channels::VOLUME_24, 0);
	if (ret == 8)
		createDamage = true;
	if (ret == (-1))
		done = true;
}

void ThugStrike::Destroy()
{
	character->setAnimationActive(false);
	character->sprite->orderLayer -= orderAdd;
	if (mover != NULL)
		delete mover;
}
