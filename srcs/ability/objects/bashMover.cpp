
#include "../../../hdr/global.h"

BashMover::BashMover(Character *attacker, Character *target, SDL_Point targetLangingPos)
{
	BashMover::attacker = attacker;
	BashMover::target = target;
	targetPoint = targetLangingPos;
	Vector place = gameState.battle.ground->GetCharacterCoord(targetPoint, target);
	SDL_Point start = {target->sprite->dest.x, target->sprite->dest.y};
	target->setAnimationActive(true);
	arch = new ThrowArch(target->sprite, start, {(int)place.x, (int)place.y}, 8000.0f, 180.0f);
	standArch = new ThrowArch(target->stand, start, {(int)place.x, (int)place.y}, 8000.0f, 180.0f);
	tStart = target->position;
	SDL_Rect dest = gameState.battle.ground->getTileDest(target->position);
	SDL_Point pos = {dest.x + 2500, dest.y + 1500};
	CreateDust(pos, Vector(-1.0f, 0.0f));
	CreateDust(pos, Vector(1.0f, 0.0f));
}

void BashMover::Update()
{
	if (done)
		return ;
	arch->Update();
	standArch->Update();
	if (arch->done || standArch->done)
	{
		SDL_Rect dest = gameState.battle.ground->getTileDest(targetPoint);
		SDL_Point pos = {dest.x + 2500, dest.y + 1500};
		CreateDust(pos, Vector(-1.0f, 0.0f));
		CreateDust(pos, Vector(1.0f, 0.0f));
		done = true;
	}
}

void BashMover::Destroy()
{
	if (arch != NULL)
		delete (arch);
	if (standArch != NULL)
		delete (standArch);
	gameState.battle.ground->PlaceCharacter(targetPoint, target);
	target->setAnimationActive(false);
	gameState.battle.ground->map[tStart.y][tStart.x].blocked = false;
	gameState.battle.ground->map[tStart.y][tStart.x].character = NULL;
}
