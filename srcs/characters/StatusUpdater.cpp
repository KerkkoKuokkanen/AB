
#include "../../hdr/global.h"

Character *current = NULL;
bool removeToxicBlade = false;

void ResetStatusUpdates()
{
	current = NULL;
	removeToxicBlade = false;
}

static Character *FindTheCharacter()
{
	if (gameState.updateObjs.turnOrder->turnChange ||
		gameState.updateObjs.turnOrder->turnStartActive)
		return (NULL);
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *targ = gameState.battle.ground->characters[i].character;
		if (targ->turn)
			return (targ);
	}
	return (NULL);
}

static void ApplyPoison(Character *character)
{
	if (character->killed)
		return ;
	gameState.updateObjs.abilities->CreatePoisonDamage(character, (int)character->statuses.poison.size());
}

static void ApplyBleed(Character *character)
{
	if (character->killed)
		return ;
	gameState.updateObjs.abilities->CreateBleedDamage(character, (int)character->statuses.bleed.size());
}

static void ManageStatuses(Character *character)
{
	if (character == NULL)
		return ;
	t_StatusEffects &statuses = character->statuses;
	for (int i = 0; i < statuses.burns.size(); i++)
	{
		statuses.burns[i] -= 1;
		if (statuses.burns[i] <= 0)
		{
			statuses.burns.erase(statuses.burns.begin() + i);
			i = (statuses.burns.size() == 0) ? 0 : i - 1;
		}
	}
	if (statuses.poison.size() != 0)
		ApplyPoison(character);
	for (int i = 0; i < statuses.poison.size(); i++)
	{
		statuses.poison[i] -= 1;
		if (statuses.poison[i] <= 0)
		{
			statuses.poison.erase(statuses.poison.begin() + i);
			i = (statuses.poison.size() == 0) ? 0 : i - 1;
		}
	}
	if (statuses.bleed.size() != 0)
		ApplyBleed(character);
	for (int i = 0; i < statuses.bleed.size(); i++)
	{
		statuses.bleed[i] -= 1;
		if (statuses.bleed[i] <= 0)
		{
			statuses.bleed.erase(statuses.bleed.begin() + i);
			i = (statuses.bleed.size() == 0) ? 0 : i - 1;
		}
	}
	if (statuses.stun > 0)
	{
		statuses.stun -= 1;
		gameState.updateObjs.turnOrder->ActivateTurnChange();
	}
}

static void ManageToxicBlade(Character *ret)
{
	if (current != NULL && current != ret && current->cSing == RAIDER)
		removeToxicBlade = true;
	if (!removeToxicBlade)
		return ;
	if (current == NULL)
		return ;
	removeToxicBlade = false;
	for (int i = 0; i < current->statuses.toxicBlade.size(); i++)
	{
		current->statuses.toxicBlade[i].turns -= 1;
		if (current->statuses.toxicBlade[i].turns < 0)
		{
			current->statuses.toxicBlade.erase(current->statuses.toxicBlade.begin() + i);
			i = (current->statuses.toxicBlade.size() == 0) ? 0 : i - 1;
		}
	}
}

static void BuffsAtEnd(Character *character)
{
	if (character == NULL)
		return ;
	t_StatusEffects &statuses = character->statuses;
	for (int i = 0; i < statuses.buffs.size(); i++)
	{
		if (!statuses.buffs[i].atEnd)
			continue ;
		statuses.buffs[i].turns -= 1;
		if (statuses.buffs[i].turns <= 0)
		{
			statuses.buffs.erase(statuses.buffs.begin() + i);
			i = (statuses.buffs.size() == 0) ? 0 : i - 1;
		}
	}
	for (int i = 0; i < statuses.deBuffs.size(); i++)
	{
		if (!statuses.buffs[i].atEnd)
			continue ;
		statuses.deBuffs[i].turns -= 1;
		if (statuses.deBuffs[i].turns <= 0)
		{
			statuses.deBuffs.erase(statuses.deBuffs.begin() + i);
			i = (statuses.deBuffs.size() == 0) ? 0 : i - 1;
		}
	}
}

static void BuffsAtStart(Character *character)
{
	if (character == NULL)
		return ;
	t_StatusEffects &statuses = character->statuses;
	for (int i = 0; i < statuses.buffs.size(); i++)
	{
		if (statuses.buffs[i].atEnd)
			continue ;
		statuses.buffs[i].turns -= 1;
		if (statuses.buffs[i].turns <= 0)
		{
			statuses.buffs.erase(statuses.buffs.begin() + i);
			i = (statuses.buffs.size() == 0) ? 0 : i - 1;
		}
	}
	for (int i = 0; i < statuses.deBuffs.size(); i++)
	{
		if (statuses.buffs[i].atEnd)
			continue ;
		statuses.deBuffs[i].turns -= 1;
		if (statuses.deBuffs[i].turns <= 0)
		{
			statuses.deBuffs.erase(statuses.deBuffs.begin() + i);
			i = (statuses.deBuffs.size() == 0) ? 0 : i - 1;
		}
	}
}

static void ManageHosting()
{
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *ret = gameState.battle.ground->characters[i].character;
		if (ret->damaged && ret->statuses.hosting != NULL)
		{
			Character *targ = (Character*)ret->statuses.hosting;
			targ->statuses.hosted = false;
			ret->statuses.hosting = NULL;
		}
		if (ret->killed && ret->statuses.hosting != NULL)
		{
			Character *targ = (Character*)ret->statuses.hosting;
			targ->statuses.hosted = false;
			ret->statuses.hosting = NULL;
		}
		if (ret->statuses.hosting != NULL)
		{
			Character *targ = (Character*)ret->statuses.hosting;
			if (targ->killed)
			{
				targ->statuses.hosted = false;
				ret->statuses.hosting = NULL;
			}
		}
	}
}

void UpdateStatuses()
{
	Character *ret = FindTheCharacter();
	ManageHosting();
	ManageToxicBlade(ret);
	if (current != ret)
	{
		BuffsAtEnd(current);
		current = ret;
		if (current == NULL)
			return ;
		BuffsAtStart(current);
		ManageStatuses(current);
	}
}
