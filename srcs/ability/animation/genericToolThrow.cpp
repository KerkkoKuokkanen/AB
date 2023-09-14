
#include "../../../hdr/global.h"

void GenericToolThrow::GetToolBox()
{
	box = (ToolBox*)gameState.battle.ground->map[boxPos.y][boxPos.x].additional.object;
}

void GenericToolThrow::SetSelector()
{
	int throwRange = (character->cSing == LION) ? 10 : 9;
	selector = new TileSelector(character->position, throwRange, 0, coloring, true);
	selector->RemovePoint(character->position);
}

GenericToolThrow::GenericToolThrow(Character *character, SDL_Point target, GroundColoring *coloring)
{
	boxPos = target;
	GetToolBox();
	GenericToolThrow::character = character;
	GenericToolThrow::coloring = coloring;
	SetSelector();
}

void GenericToolThrow::CreateMover()
{
	SDL_Rect dest1 = gameState.battle.ground->getTileDest(character->position);
	SDL_Rect dest2 = gameState.battle.ground->getTileDest(boxDest);
	Vector dir = Vector((float)(dest2.x - dest1.x), (float)(dest2.y - dest1.y)).Normalized();
	mover = new CharacterMover(character, dir, 13, 13, 280.0f);
	character->setAnimationActive(true);
}

void GenericToolThrow::UpdateSelector()
{
	if (selector == NULL)
		return ;
	coloring->active = true;
	SDL_Point ret = selector->Update();
	if (ret.x != (-1) && ret.y != (-1))
	{
		if (gameState.keys.click == RELEASE_CLICK)
		{
			boxDest = ret;
			delete selector;
			selector = NULL;
			coloring->ClearMap();
			coloring->active = false;
			secondPhase = true;
			CreateMover();
		}
	}
}

void GenericToolThrow::UpdateSecondPhase()
{
	if (!secondPhase)
		return ;
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
	UpdateSelector();
	UpdateSecondPhase();
}

void GenericToolThrow::Destroy()
{
	if (mover != NULL)
		delete mover;
	if (selector != NULL)
		delete selector;
	character->setAnimationActive(false);
}
