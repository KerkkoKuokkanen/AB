
#include "../../../hdr/global.h"

void Supply::GetToolBox(SDL_Point target)
{
	box = (ToolBox*)gameState.battle.ground->map[target.y][target.x].additional.object;
}

Supply::Supply(Character *character, SDL_Point target)
{
	Supply::character = character;
	GetToolBox(target);
	SDL_Rect dest1 = gameState.battle.ground->getTileDest(character->position);
	SDL_Rect dest2 = gameState.battle.ground->getTileDest(target);
	Vector dir = Vector((float)(dest2.x - dest1.x), (float)(dest2.y - dest1.y)).Normalized();
	mover = new CharacterMover(character, dir, 12, 12, 250.0f);
	character->setAnimationActive(true);
}

void Supply::Update()
{
	if (done)
		return ;
	int ret =  mover->Update();
	if (ret == 10)
		box->SupplyTarget(character);
	if (ret == (-1))
		done = true;
}

void Supply::Destroy()
{
	character->setAnimationActive(false);
	if (mover != NULL)
		delete mover;
}
