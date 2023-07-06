
#include "../../hdr/global.h"

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
			tileSelector = new TileSelector(pos, 7, 0, &groundColoring);
			tileSelector->IncludePoint(pos);
			break ;
	}
}

void Abilities::SetAbility(t_Ability *ability, Character *character)
{
	gameState.updateObjs.turnOrder->ResetClicks();
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
			target = blockChar;
			targetPoint = ret;
			ActivateAbility(ability, character);
			ClearMap();
		}
	}
}

void Abilities::UpdateSelector()
{
	if (selector != NULL)
		SelectorWithCharacters();
	else if (tileSelector != NULL)
		SelectorWithSquares();
}

void Abilities::Upadte()
{
	UpdateSelector();
	AnimationUpdater();
	ObjectUpdater();
	effectUpdater.Update();
	damager.Update();
	groundColoring.Update();
	if (gameState.keys.rightClick == INITIAL_CLICK)
		ClearMap();
	AbilityStatus();
}

void Abilities::UpdateSpecificAnimation(t_Animation &animation, int index)
{
	switch (animation.type)
	{
		case DAGGER_THROW:
		{
			DaggerThrowAnim *used = (DaggerThrowAnim*)animation.animation;
			used->Update();
			if (used->timeForAbility)
			{
				int chance = GetChance(character, target, ability);
				Character *ret = RangedCheck(character, target, chance);
				targetPoint = ret->position;
				objects.push_back({new Dagger(character, ret, chance), DAGGER_OBJ});
			}
			if (!used->active)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case SMOKE_BOMB:
		{
			SmokeBombAnim *use = (SmokeBombAnim*)animation.animation;
			use->Update();
			if (!use->active)
			{
				delete use;
				animations.erase(animations.begin() + index);
			}
			if (use->timeForAbility)
				objects.push_back({new SmokeBomb(character->position, targetPoint), SMOKE_OBJ});
			break ;
		}
		case DAGGER_SLASH:
		{
			DaggerSlashAnim *use = (DaggerSlashAnim*)animation.animation;
			use->Update();
			if (use->createDamage)
			{
				if (MeleeCheck(character, target, ability))
					CreateDamage();
				else
					PlaySound(gameState.audio.whiff, Channels::WHIFF, 0);
			}
			if (use->done)
			{
				delete use;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
	}
}

void Abilities::AnimationUpdater()
{
	for (int i = 0; i < animations.size(); i++)
	{
		UpdateSpecificAnimation(animations[i], i);
	}
}

void Abilities::CreateDamage()
{
	std::vector<SDL_Point> used = {targetPoint};
	damager.AddDamage(ability, character, used);
}

void Abilities::UpdateSpecificObject(t_Object &object, int index)
{
	switch (object.type)
	{
		case DAGGER_OBJ:
		{
			Dagger *used = (Dagger*)object.object;
			used->Update();
			if (used->remove)
			{
				if (used->createDamage)
					CreateDamage();
				delete used;
				objects.erase(objects.begin() + index);
			}
			break ;
		}
		case SMOKE_OBJ:
		{
			SmokeBomb *used = (SmokeBomb*)object.object;
			used->Update();
			if (used->setEffect)
				effectUpdater.SetEffect(2, targetPoint, *ability);
			if (used->destroy)
			{
				delete used;
				objects.erase(objects.begin() + index);
			}
			break ;
		}
	}
}

void Abilities::ObjectUpdater()
{
	for (int i = 0; i < objects.size(); i++)
	{
		UpdateSpecificObject(objects[i], i);
	}
}

void Abilities::AbilityStatus()
{
	if (!inMotion)
		return ;
	if (objects.size() == 0 && animations.size() == 0)
		Clear();
}

void Abilities::ClearMap()
{
	if (selector != NULL)
		delete selector;
	selector = NULL;
	if (tileSelector != NULL)
		delete tileSelector;
	tileSelector = NULL;
	groundColoring.ClearMap();
	groundColoring.active = false;
	if (!inMotion)
		active = false;
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
	active = false;
	target = NULL;
	groundColoring.ClearMap();
	groundColoring.active = false;
	inMotion = false;
}
