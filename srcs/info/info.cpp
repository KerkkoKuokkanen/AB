
#include "../../hdr/global.h"

bool NoOneClicked()
{
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		if (gameState.battle.ground->characters[i].character->clicked)
			return (false);
	}
	return (true);
}

Info::Info()
{
	hoverBars = new HoverBars;
	counter = new Counter;
	hovered = NULL;
}

void Info::FindHoveredCharacter()
{
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		if (gameState.battle.ground->characters[i].character->hover)
		{
			hovered = gameState.battle.ground->characters[i].character;
			if (hovered->turn || hovered->active == false || !NoOneClicked())
				hovered = NULL;
			return ;
		}
	}
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (gameState.battle.ground->map[i][j].marked &&
				gameState.battle.ground->map[i][j].character != NULL)
			{
				hovered = gameState.battle.ground->map[i][j].character;
				if (hovered->turn || hovered->active == false || !NoOneClicked())
					hovered = NULL;
				return ;
			}
		}
	}
	hovered = NULL;
}

void Info::Update()
{
	FindHoveredCharacter();
	hoverBars->Update(hovered);
	counter->Update();
	overInfo = counter->insideBox;
}

void Info::Destroy()
{
	delete hoverBars;
	delete counter;
}
