
#include "../../hdr/global.h"

static void SetSelectorForRotate(t_Ability *ability, Selector *selector)
{
	int *tier = (int*)ability->stats;
	selector->ClearStunned(true, false);
	if (*tier == 1)
		selector->SetSelectorFor(true, false);
	else
		selector->SetSelectorFor(true, true);
}

void Abilities::SetSelector(t_Ability *ability, Character *character)
{
	SDL_Point pos = character->position;
	switch(ability->type)
	{
		case DAGGER_THROW:
			selector = new Selector(pos, 13, 2, &groundColoring, false, true); // have to chance these hardCoded numbers later
			break ;
		case DAGGER_SLASH:
			selector = new Selector(pos, 2, 0, &groundColoring, true, false);
			break ;
		case SMOKE_BOMB:
			tileSelector = new TileSelector(pos, 7, 0, &groundColoring, false);
			tileSelector->IncludePoint(pos);
			break ;
		case FLAME_PORT:
			tileSelector = new TileSelector(pos, 15, 0, &groundColoring, true);
			break ;
		case FLAME_SLASH:
			selector = new Selector(pos, 2, 0, &groundColoring, true, false);
			break ;
		case FLAME_BLAST:
			multiSelector = new MultiSelector(pos, 6, 0, &groundColoring, false, true, 2);
			break ;
		case INCINERATE:
			allSelector = new AllSelector(pos, 6, 0, &groundColoring, true, StatusSigns::BURN);
			break ;
		case LION_SMACK:
			selector = new Selector(pos, 2, 0, &groundColoring, true, false);
			break ;
		case PHANTOM_KNIGHT:
			phantSelector = new PhantomSelector(character, 8, &groundColoring);
			break ;
		case ROTATE:
			selector = new Selector(pos, 2, 0, &groundColoring, true, false);
			SetSelectorForRotate(ability, selector);
			break ;
		case HAMMER_SMACK:
			selector = new Selector(pos, 2, 0, &groundColoring, true, false);
			break ;
	}
}

void Abilities::SetAbility(t_Ability *ability, Character *character)
{
	gameState.updateObjs.turnOrder->ResetClicks();
	if (CheckForPhantomKnight())
		return ;
	if (inMotion)
		return ;
	Clear();
	Abilities::ability = ability;
	Abilities::character = character;
	SetSelector(ability, character);
	active = true;
}

void Abilities::ActivateAbility(t_Ability *ability, Character *character)
{
	inMotion = true;
	switch (ability->type)
	{
		case DAGGER_THROW:
			animations.push_back({new DaggerThrowAnim(character, target), DAGGER_THROW});
			break ;
		case SMOKE_BOMB:
			animations.push_back({new SmokeBombAnim(character, targetPoint), SMOKE_BOMB});
			break ;
		case DAGGER_SLASH:
			animations.push_back({new DaggerSlashAnim(character, targetPoint), DAGGER_SLASH});
			break ;
		case FLAME_PORT:
			animations.push_back({new FlamePort(character, targetPoint), FLAME_PORT});
			break ;
		case FLAME_SLASH:
			animations.push_back({new FlameSlash(character, targetPoint), FLAME_SLASH});
			break ;
		case FLAME_BLAST:
			animations.push_back({new FlameBlast(character, targPoints, ability), FLAME_BLAST});
			break ;
		case INCINERATE:
			if (targPoints.size() != 0)
				animations.push_back({new Incinerate(character, targPoints), INCINERATE});
			break ;
		case LION_SMACK:
			animations.push_back({new LionSmack(character, targetPoint), LION_SMACK});
			break ;
		case PHANTOM_KNIGHT:
			SetScreenShake(300, 8);
			animations.push_back({new PhantomAnim(targPoints), PHANTOM_KNIGHT});
			break ;
		case ROTATE:
			animations.push_back({new Rotate(character, target), ROTATE});
			break ;
		case HAMMER_SMACK:
			animations.push_back({new HammerSmack(character, target), HAMMER_SMACK});
			break ;
	}
}

void Abilities::SelectorWithCharacters()
{
	gameState.updateObjs.UI->ShowEnergy(ability->cost);
	Character *ret = selector->Update();
	if (ret != NULL)
	{
		if (gameState.keys.click == RELEASE_CLICK)
		{
			gameState.updateObjs.UI->UseEnergy(ability->cost);
			character->stats.fatigue += ability->fatigue;
			target = ret;
			targetPoint = ret->position;
			ActivateAbility(ability, character);
			ClearMap();
		}
	}
}

void Abilities::SelectorWithSquares()
{
	gameState.updateObjs.UI->ShowEnergy(ability->cost);
	SDL_Point ret = tileSelector->Update();
	if (ret.x != (-1) && ret.y != (-1))
	{
		Character *blockChar = gameState.battle.ground->map[ret.y][ret.x].character;
		if (gameState.keys.click == RELEASE_CLICK)
		{
			gameState.updateObjs.UI->UseEnergy(ability->cost);
			character->stats.fatigue += ability->fatigue;
			target = blockChar;
			targetPoint = ret;
			ActivateAbility(ability, character);
			ClearMap();
		}
	}
}

void Abilities::UpdatePhantomSelector()
{
	gameState.updateObjs.UI->ShowEnergy(ability->cost);
	phantSelector->Update();
	if (phantSelector->done)
	{
		targPoints.clear();
		gameState.updateObjs.UI->UseEnergy(ability->cost);
		character->stats.fatigue += ability->fatigue;
		targPoints = phantSelector->GetTargets();
		if (targPoints.size() != 0)
			ActivateAbility(ability, character);
		ClearMap();
	}
}

void Abilities::MultiSelectorWithCharacter()
{
	gameState.updateObjs.UI->ShowEnergy(ability->cost);
	multiSelector->Update();
	if (!multiSelector->done)
		return ;
	gameState.updateObjs.UI->UseEnergy(ability->cost);
	character->stats.fatigue += ability->fatigue;
	targPoints.clear();
	targPoints = multiSelector->GetPositions();
	ActivateAbility(ability, character);
	ClearMap();
}

void Abilities::AllSelectorUpdate()
{
	gameState.updateObjs.UI->ShowEnergy(ability->cost);
	allSelector->Update();
	if (allSelector->done)
	{
		gameState.updateObjs.UI->UseEnergy(ability->cost);
		character->stats.fatigue += ability->fatigue;
		targPoints.clear();
		targPoints = allSelector->getTargets();
		ActivateAbility(ability, character);
		ClearMap();
	}
}

void Abilities::UpdateSelector()
{
	if (selector != NULL)
		SelectorWithCharacters();
	else if (tileSelector != NULL)
		SelectorWithSquares();
	else if (multiSelector != NULL)
		MultiSelectorWithCharacter();
	else if (allSelector != NULL)
		AllSelectorUpdate();
	else if (phantSelector != NULL)
		UpdatePhantomSelector();
}

void Abilities::UpdateMisses()
{
	for (int i = 0; i < misses.size(); i++)
	{
		int ret = misses[i]->Update();
		if (ret == (-1))
		{
			delete misses[i];
			misses.erase(misses.begin() + i);
			i = (i == 0) ? 0 : i - 1;
		}
	}
}

void Abilities::Upadte()
{
	UpdateSelector();
	AnimationUpdater();
	ObjectUpdater();
	UpdateMisses();
	oAttack.Update();
	effectUpdater.Update();
	damager.Update();
	groundColoring.Update();
	if (gameState.keys.rightClick == INITIAL_CLICK)
		ClearMap();
	AbilityStatus();
}

void Abilities::HandleDamageVector(std::vector<t_HitReturn> &ret)
{
	for (int i = 0; i < ret.size(); i++)
	{
		if (!ret[i].missing)
		{
			std::vector<SDL_Point> add = {ret[i].target};
			damager.AddDamage(ability, character, add);
		}
		else
			PlaySound(gameState.audio.whiff, Channels::WHIFF, 0);
	}
}

void Abilities::AnimationUpdater()
{
	for (int i = 0; i < animations.size(); i++)
	{
		if (animations[i].type == ROTATE)
		{
			UpdateRotate(i);
			continue ;
		}
		switch (character->cSing)
		{
			case THIEF:
				UpdateThiefAnimation(animations[i], i);
				break ;
			case PYRO:
				UpdatePyroAnimation(animations[i], i);
				break ;
			case LION:
				UpdateLionAnimation(animations[i], i);
				break ;
			case SMITH:
				UpdateSmithAnimation(animations[i], i);
				break ;
		}
	}
}

void Abilities::CreateDamage(bool sound)
{
	std::vector<SDL_Point> used = {targetPoint};
	damager.AddDamage(ability, character, used, sound);
}

void Abilities::ObjectUpdater()
{
	for (int i = 0; i < objects.size(); i++)
	{
		switch (character->cSing)
		{
			case THIEF:
				UpdateThiefObject(objects[i], i);
				break ;
		}
	}
}

void Abilities::AbilityStatus()
{
	if (!inMotion)
		return ;
	if (objects.size() == 0 && animations.size() == 0)
		Clear();
}

void Abilities::CreateOpportunityDamage(Character *damager, Character *target)
{
	Abilities::damager.AddOpportunityDamage(damager, target);
}

void Abilities::ClearMap()
{
	if (selector != NULL)
		delete selector;
	selector = NULL;
	if (tileSelector != NULL)
		delete tileSelector;
	tileSelector = NULL;
	if (multiSelector != NULL)
		delete multiSelector;
	multiSelector = NULL;
	if (allSelector != NULL)
		delete allSelector;
	allSelector = NULL;
	if (phantSelector != NULL)
		delete phantSelector;
	phantSelector = NULL;
	groundColoring.ClearMap();
	groundColoring.active = false;
	if (!inMotion)
		active = false;
	marking = false;
}

void Abilities::Clear()
{
	ability = NULL;
	character = NULL;
	if (selector != NULL)
		delete selector;
	selector = NULL;
	if (tileSelector != NULL)
		delete tileSelector;
	tileSelector = NULL;
	if (multiSelector != NULL)
		delete multiSelector;
	multiSelector = NULL;
	if (allSelector != NULL)
		delete allSelector;
	allSelector = NULL;
	if (phantSelector != NULL)
		delete phantSelector;
	phantSelector = NULL;
	active = false;
	target = NULL;
	targetPoint = {-1, -1};
	targPoints.clear();
	groundColoring.ClearMap();
	groundColoring.active = false;
	inMotion = false;
	marking = false;
}
