
#include "../../../hdr/global.h"

static bool ValidPosition(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	return (true);
}

bool PickUpTools::gotTheBox(SDL_Point pos)
{
	int x = pos.x;
	int y = pos.y;
	if (ValidPosition(pos))
	{
		if (gameState.battle.ground->map[y][x].additional.object != NULL)
		{
			if (gameState.battle.ground->map[y][x].additional.type == AdditionalObjects::TOOLBOX)
			{
				ToolBox *used = (ToolBox*)gameState.battle.ground->map[y][x].additional.object;
				if (used->character == character)
				{
					target = used;
					return (true);
				}
			}
		}
	}
	return (false);
}

void PickUpTools::GetToolBox()
{
	target = NULL;
	SDL_Point pos = character->position;
	int x = getXToLeft(pos);
	int y = pos.y - 1;
	if (gotTheBox({x, y}))
		return ;
	y = pos.y + 1;
	if (gotTheBox({x, y}))
		return ;
	x = getXToRight(pos);
	y = pos.y - 1;
	if (gotTheBox({x, y}))
		return ;
	y = pos.y + 1;
	gotTheBox({x, y});
}

PickUpTools::PickUpTools(Character *character)
{
	PickUpTools::character = character;
	GetToolBox();
	if (target == NULL)
	{
		done = true;
		return ;
	}
	SDL_Point pos = target->getPosition();
	SDL_Rect dest1 = gameState.battle.ground->getTileDest(character->position);
	SDL_Rect dest2 = gameState.battle.ground->getTileDest(pos);
	Vector dir = Vector((float)(dest2.x - dest1.x), (float)(dest2.y - dest1.y)).Normalized();
	mover = new CharacterMover(character, dir, 12, 12, 250.0f);
	character->setAnimationActive(true);
}

void PickUpTools::Update()
{
	if (done)
		return ;
	int ret = mover->Update();
	if (ret == 10)
		target->SetToolBoxBack();
	if (ret == (-1))
		done = true;
}

void PickUpTools::Destroy()
{
	if (mover != NULL)
		delete mover;
	character->setAnimationActive(false);
}
