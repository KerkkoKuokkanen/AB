
#include "../../hdr/global.h"

static Character *AnyOneClicked()
{
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *character = gameState.battle.ground->characters[i].character;
		if (character->clicked)
			return (character);
	}
	return (NULL);
}

Info::Info()
{
	counter = new Counter;
	stunUpdates = new StunUpdates;
	controls = new ControlSetter;
	movementEnergy = new MovementEnergy;
	colorEffects = new ColorEffects;
	healthColoring = new HealthColoring;
	statusInfo = new StatusInfo;
	hitChanceBubble = new HitChanceBubble;
	statusInfo->SetXAndYAdd(600, 600);
	hovered = NULL;
}

void Info::InitInfo()
{
	iconHandler = new IconBarHandler;
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
	hoverIcon = (-1);
	overInfoBar = false;
	Character *ret = AnyOneClicked();
	if (ret != NULL && !ret->turn)
	{
		if (bar == NULL || bar->character == NULL)
		{
			delete bar;
			bar = new InfoBar(ret);
		}
		else if (bar->character != ret)
		{
			delete bar;
			bar = new InfoBar(ret);
		}
		bar->statBars = true;
		bar->Update();
		hoverIcon = bar->hoverIcon;
		overInfoBar = bar->over;
		return ;
	}
	if (hovered == NULL || hovered->killed)
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
	bar->statBars = false;
	bar->Update();
	overInfoBar = bar->over;
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

void Info::UpdateSupplyEffects()
{
	for (int i = 0; i < supplyEffects.size(); i++)
	{
		supplyEffects[i]->Update();
		if (supplyEffects[i]->done)
		{
			delete supplyEffects[i];
			supplyEffects.erase(supplyEffects.begin() + i);
			i = (supplyEffects.size() == 0) ? 0 : i - 1;
		}
	}
}

void Info::UpdateBuffEffects()
{
	for (int i = 0; i < buffEffects.size(); i++)
	{
		buffEffects[i]->Update();
		if (buffEffects[i]->done)
		{
			delete buffEffects[i];
			buffEffects.erase(buffEffects.begin() + i);
			i = (buffEffects.size() == 0) ? 0 : i - 1;
		}
	}
}

void Info::UpdateHostEffects()
{
	for (int i = 0; i < hostEffects.size(); i++)
	{
		hostEffects[i]->Update();
		if (hostEffects[i]->done)
		{
			delete hostEffects[i];
			hostEffects.erase(hostEffects.begin() + i);
			i = (buffEffects.size() == 0) ? 0 : i - 1;
		}
	}
}

void Info::UpdateBombEffects()
{
	for (int i = 0; i < nailBombs.size(); i++)
	{
		nailBombs[i]->Update();
		if (nailBombs[i]->done)
		{
			delete nailBombs[i];
			nailBombs.erase(nailBombs.begin() + i);
			i = (nailBombs.size() == 0) ? 0 : i - 1;
		}
	}
	for (int i = 0; i < acidBombs.size(); i++)
	{
		acidBombs[i]->Update();
		if (acidBombs[i]->done)
		{
			delete acidBombs[i];
			acidBombs.erase(acidBombs.begin() + i);
			i = (acidBombs.size() == 0) ? 0 : i - 1;
		}
	}
}

void Info::UpdateSlowEffects()
{
	for (int i = 0; i < slowEffects.size(); i++)
	{
		slowEffects[i]->Update();
		if (slowEffects[i]->done)
		{
			delete slowEffects[i];
			slowEffects.erase(slowEffects.begin() + i);
			i = (slowEffects.size() == 0) ? 0 : i - 1;
		}
	}
	for (int i = 0; i < healEffects.size(); i++)
	{
		healEffects[i]->Update();
		if (healEffects[i]->done)
		{
			delete healEffects[i];
			healEffects.erase(healEffects.begin() + i);
			i = (healEffects.size() == 0) ? 0 : i - 1;
		}
	}
	for (int i = 0; i < shieldBashEffects.size(); i++)
	{
		shieldBashEffects[i]->Update();
		if (shieldBashEffects[i]->done)
		{
			delete shieldBashEffects[i];
			shieldBashEffects.erase(shieldBashEffects.begin() + i);
			i = (shieldBashEffects.size() == 0) ? 0 : i - 1;
		}
	}
}

void Info::AddBombEffect(void *effect, int abilityType)
{
	switch (abilityType)
	{
		case NAIL_BOMB:
		{
			NailBombBlast *used = (NailBombBlast*)effect;
			nailBombs.push_back(used);
			break ;
		}
		case ACID_BOMB:
		{
			AcidBombBlast *used = (AcidBombBlast*)effect;
			acidBombs.push_back(used);
			break ;
		}

	}
}

void Info::UpdateCritFilter()
{
	if (critFilter.sprite == NULL)
		return ;
	critFilter.time -= 1;
	if (critFilter.time > 20)
	{
		int count = 30 - critFilter.time;
		int alpha = 30 + (15 * count);
		critFilter.sprite->AlphaMod(alpha);
		return ;
	}
	if (critFilter.time <= 0)
	{
		delete critFilter.sprite;
		critFilter.sprite = NULL;
		return ;
	}
	if (critFilter.time <= 10)
	{
		int count = 10 - critFilter.time;
		int alpha = 165 - (15 * count);
		critFilter.sprite->AlphaMod(alpha);
	}
}

void Info::UpdateStatusInfo()
{
	statusInfo->Update(hoverIcon);
}

void Info::Update()
{
	FindHoveredCharacter();
	UpdateBar();
	UpdateSnippets();
	UpdateSupplyEffects();
	UpdateBuffEffects();
	UpdateHostEffects();
	UpdateBombEffects();
	UpdateSlowEffects();
	UpdateCritFilter();
	UpdateStatusInfo();
	counter->Update();
	stunUpdates->Update();
	controls->Update();
	movementEnergy->Update();
	healthColoring->Update();
	colorEffects->Update();
	iconHandler->Update();
	hitChanceBubble->Update(hovered);
	overInfo = counter->insideBox;
}

void Info::SetCritFilter()
{
	if (critFilter.sprite != NULL)
		delete critFilter.sprite;
	critFilter.sprite = new Sprite(gameState.textures.critFilter, {-50000, -50000, 100000, 57000}, NULL, NULL, 0, FLIP_NONE, true);
	critFilter.sprite->orderLayer = 10;
	critFilter.sprite->AlphaMod(30);
	critFilter.sprite->ColorMod(97, 9, 9);
	critFilter.time = 30;
	gameState.render->AddSprite(critFilter.sprite, FILTER_LAYER);
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
	delete colorEffects;
	delete iconHandler;
	if (stunUpdates != NULL)
		delete stunUpdates;
	for (int i = 0; i < snippets.size(); i++)
		delete snippets[i];
	snippets.clear();
	for (int i = 0; i < supplyEffects.size(); i++)
		delete supplyEffects[i];
	for (int i = 0; i < nailBombs.size(); i++)
		delete nailBombs[i];
	for (int i = 0; i < hostEffects.size(); i++)
		delete hostEffects[i];
	for (int i = 0; i < buffEffects.size(); i++)
		delete buffEffects[i];
	supplyEffects.clear();
}
