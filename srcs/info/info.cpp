
#include "../../hdr/global.h"

Info::Info()
{
	counter = new Counter;
	stunUpdates = new StunUpdates;
	controls = new ControlSetter;
	movementEnergy = new MovementEnergy;
	hovered = NULL;
}

void Info::FindHoveredCharacter()
{
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		if (gameState.battle.ground->characters[i].character->hover)
		{
			hovered = gameState.battle.ground->characters[i].character;
			if ((hovered->turn && hovered->ally) || hovered->active == false)
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
				if ((hovered->turn && hovered->ally) || hovered->active == false)
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

void Info::UpdateBar()
{
	if (hovered == NULL)
	{
		if (bar != NULL)
			delete bar;
		bar = NULL;
		return ;
	}
	if (bar == NULL)
		bar = new InfoBar(hovered);
	else if (bar->character != hovered)
	{
		delete bar;
		bar = new InfoBar(hovered);
	}
	bar->Update();
}

void Info::UpdateSnippets()
{
	for (int i = 0; i < snippets.size(); i++)
	{
		snippets[i]->Update();
		if (snippets[i]->done)
		{
			delete snippets[i];
			snippets.erase(snippets.begin() + i);
			i = (i == 0) ? 0 : i - 1;
		}
	}
}

void Info::Update()
{
	FindHoveredCharacter();
	UpdateBar();
	UpdateSnippets();
	counter->Update();
	stunUpdates->Update();
	controls->Update();
	movementEnergy->Update();
	overInfo = counter->insideBox;
}

void Info::AddSnippet(FlyingSnippet *snippet)
{
	snippets.push_back(snippet);
}

void Info::Destroy()
{
	delete counter;
	delete movementEnergy;
	delete controls;
	if (stunUpdates != NULL)
		delete stunUpdates;
}
