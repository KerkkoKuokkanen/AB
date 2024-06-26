
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
	int num = 0;
	for (int i = 0; i < character->statuses.poison.size(); i++)
		num += character->statuses.poison[i].x;
	gameState.updateObjs.abilities->CreatePoisonDamage(character, num);
}

static void ApplyBleed(Character *character)
{
	if (character->killed)
		return ;
	int num = 0;
	for (int i = 0; i < character->statuses.bleed.size(); i++)
		num += character->statuses.bleed[i].x;
	gameState.updateObjs.abilities->CreateBleedDamage(character, num);
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
		statuses.poison[i].y -= 1;
		if (statuses.poison[i].y <= 0)
		{
			statuses.poison.erase(statuses.poison.begin() + i);
			i = (statuses.poison.size() == 0) ? 0 : i - 1;
		}
	}
	if (statuses.bleed.size() != 0)
		ApplyBleed(character);
	for (int i = 0; i < statuses.bleed.size(); i++)
	{
		statuses.bleed[i].y -= 1;
		if (statuses.bleed[i].y <= 0)
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
	if (statuses.controlZone > 0)
		statuses.controlZone -= 1;
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
	if (character->statuses.slowed > 0)
		character->statuses.slowed -= 1;
	if (character->statuses.frenzy > 0)
		character->statuses.frenzy -= 1;
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
		if (statuses.deBuffs[i].atEnd)
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

static void AddEnergy(Character *character)
{
	character->moves = (character->moves + 9 > 12) ? 12 : character->moves + 9;
}

void AddBuffToCharacter(Character *target, t_BuffDebuff add)
{
	if (add.id <= 0)
	{
		target->statuses.buffs.push_back(add);
		return ;
	}
	for (int i = 0; i < target->statuses.buffs.size(); i++)
	{
		if (target->statuses.buffs[i].id == add.id)
		{
			target->statuses.buffs.erase(target->statuses.buffs.begin() + i);
			i = (target->statuses.buffs.size() == 0) ? 0 : 1 - 1;
		}
	}
	target->statuses.buffs.push_back(add);
}

void AddDeBuffToCharacter(Character *target, t_BuffDebuff add)
{
	if (add.id <= 0)
	{
		target->statuses.deBuffs.push_back(add);
		return ;
	}
	for (int i = 0; i < target->statuses.deBuffs.size(); i++)
	{
		if (target->statuses.deBuffs[i].id == add.id)
		{
			target->statuses.deBuffs.erase(target->statuses.deBuffs.begin() + i);
			i = (target->statuses.deBuffs.size() == 0) ? 0 : i - 1;
		}
	}
	target->statuses.deBuffs.push_back(add);
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
		AddEnergy(current);
		BuffsAtStart(current);
		ManageStatuses(current);
	}
}
