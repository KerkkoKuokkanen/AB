
#include "../../../hdr/global.h"

static void AddStatusDamageToCharacter(t_AiCharacter *character, int amount)
{
	character->health -= amount;
	if (character->health <= 0)
	{
		character->health = 0;
		character->alive = false;
	}
}

static void ManageStatuses(t_AiCharacter *character)
{
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
		AddStatusDamageToCharacter(character, (int)statuses.poison.size());
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
		AddStatusDamageToCharacter(character, (int)statuses.bleed.size());
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
	if (statuses.controlZone > 0)
		statuses.controlZone -= 1;
}

static void HandleBuffsAndDebuffs(t_AiCharacter *character)
{
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

void AiIterator::TurnStartCharacterChecks(t_AiCharacter *character)
{
	character->moves += 9;
	if (character->moves > 12)
		character->moves = 12;
	HandleBuffsAndDebuffs(character);
	ManageStatuses(character);
	CheckDeadCharacter(character, map);
}

static void TurnEndStatuses(t_AiCharacter *character)
{
	for (int i = 0; i < character->statuses.toxicBlade.size(); i++)
	{
		character->statuses.toxicBlade[i].turns -= 1;
		if (character->statuses.toxicBlade[i].turns < 0)
		{
			character->statuses.toxicBlade.erase(character->statuses.toxicBlade.begin() + i);
			i = (character->statuses.toxicBlade.size() == 0) ? 0 : i - 1;
		}
	}
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
	if (character->statuses.slowed == 1)
		character->statuses.slowed = 0;
}

void AiIterator::TurnEndChecks(t_AiCharacter *character)
{
	TurnEndStatuses(character);
}
