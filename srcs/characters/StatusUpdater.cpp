
#include "../../hdr/global.h"

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
	if (statuses.stun > 0)
	{
		statuses.stun -= 1;
		gameState.updateObjs.turnOrder->ActivateTurnChange();
	}
}

static void ManageBuffs(Character *character)
{
	if (character == NULL)
		return ;
	t_StatusEffects &statuses = character->statuses;
	for (int i = 0; i < statuses.buffs.size(); i++)
	{
		statuses.buffs[i].turns -= 1;
		if (statuses.buffs[i].turns <= 0)
		{
			statuses.buffs.erase(statuses.buffs.begin() + i);
			i = (statuses.buffs.size() == 0) ? 0 : i - 1;
		}
	}
	for (int i = 0; i < statuses.deBuffs.size(); i++)
	{
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
	ManageHosting();
	static Character *current = NULL;
	Character *ret = FindTheCharacter();
	if (current != ret)
	{
		ManageBuffs(current);
		current = ret;
		if (current == NULL)
			return ;
		ManageStatuses(current);
	}
}
