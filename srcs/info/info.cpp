
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

bool Info::KilledOrDamaged()
{
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *targ = gameState.battle.ground->characters[i].character;
		if (targ != NULL)
		{
			if (targ->killed || targ->damaged || targ->moving)
				return (true);
		}
	}
	return (false);
}

void Info::ManageFilterMode()
{
	if (gameState.modes.filterMode != 2 || gameState.updateObjs.abilities->marking || KilledOrDamaged() ||
		gameState.updateObjs.turnOrder->turnChange || gameState.updateObjs.turnOrder->turnStartActive)
	{
		if (filterMode != NULL)
		{
			delete filterMode;
			filterMode = NULL;
		}
		return ;
	}
	if (gameState.modes.filterMode == 2 && filterMode == NULL)
		filterMode = new FilterModeBars;
	if (filterMode != NULL)
		filterMode->Update();
}

void Info::Update()
{
	FindHoveredCharacter();
	ManageFilterMode();
	hoverBars->Update(hovered);
	counter->Update();
	overInfo = counter->insideBox;
}

void Info::Destroy()
{
	delete hoverBars;
	delete counter;
}
