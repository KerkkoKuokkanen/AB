
#include "../../../hdr/global.h"
#define TIME_OUT 500

static SDL_Point GetDest(SDL_Point pos)
{
	SDL_Point ret = {0, 0};
	SDL_Rect dest = gameState.battle.ground->getTileDest(pos);
	ret = {dest.x - 200, dest.y - 5000};
	return (ret);
}

AxeJumpAnim::AxeJumpAnim(Character *character, Character *target, SDL_Point pos)
{
	AxeJumpAnim::character = character;
	AxeJumpAnim::target = target;
	AxeJumpAnim::pos = pos;
}

void AxeJumpAnim::StartJump()
{
	SDL_Point start = {character->sprite->dest.x, character->sprite->dest.y};
	arch = new ThrowArch(character->sprite, start, GetDest(pos), 15.0f, 100.0f);
	character->setAnimationActive(true);
}

void AxeJumpAnim::UpdateJump()
{
	if (arch == NULL)
		return ;
	arch->Update();
	if (arch->done)
	{
		delete arch;
		arch = NULL;
		done = true;
		gameState.battle.ground->PlaceCharacter(pos, character);
	}
}

void AxeJumpAnim::Update()
{
	createDamage = false;
	if (done)
		return ;
	if (counter == 6)
		StartJump();
	UpdateJump();
	counter++;
	if (counter > TIME_OUT)
		done = true;
}

void AxeJumpAnim::Destroy()
{
	if (arch != NULL)
		delete arch;
	character->setAnimationActive(false);
}
