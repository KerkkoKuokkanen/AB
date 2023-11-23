
#include "../../../hdr/global.h"

void GenericToolThrow::GetToolBox()
{
	box = (ToolBox*)gameState.battle.ground->map[boxPos.y][boxPos.x].additional.object;
}

GenericToolThrow::GenericToolThrow(Character *character, SDL_Point target, SDL_Point goal)
{
	boxPos = target;
	boxDest = goal;
	GetToolBox();
	GenericToolThrow::character = character;
	CreateMover();
}

void GenericToolThrow::CreateMover()
{
	SDL_Rect dest1 = gameState.battle.ground->getTileDest(character->position);
	SDL_Rect dest2 = gameState.battle.ground->getTileDest(boxDest);
	Vector dir = Vector((float)(dest2.x - dest1.x), (float)(dest2.y - dest1.y)).Normalized();
	mover = new CharacterMover(character, dir, 13, 13, 280.0f);
	character->setAnimationActive(true);
}

void GenericToolThrow::UpdateSecondPhase()
{
	int ret = mover->Update();
	if (ret == 10)
		box->SetToolThrow(boxDest);
	if (ret == (-1))
		done = true;
}

void GenericToolThrow::Update()
{
	if (done)
		return ;
	UpdateSecondPhase();
}

void GenericToolThrow::Destroy()
{
	if (mover != NULL)
		delete mover;
	character->setAnimationActive(false);
}
