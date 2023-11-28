
#include "../../hdr/global.h"

int RangedChance(Character *character, Character *target)
{
	SDL_Point cPos = character->position;
	SDL_Point tPos = target->position;
	int height = gameState.battle.ground->map[cPos.y][cPos.x].height - gameState.battle.ground->map[tPos.y][tPos.x].height;
	if (height > 3)
		height = 3;
	if (height < -3)
		height = -3;
	return (5 * height);
}

int GetChance(Character *character, Character *target, t_Ability *ability)
{
	if (ability == NULL)
		return (0);
	if (ability->baseChance >= 200)
		return (200);
	int ret = ability->baseChance;
	ret += RangedChance(character, target);
	if (ret > 95)
		ret = 95;
	if (ret < 5)
		ret = 5;
	return (ret);
}

Character *BasicCheck(Character *target, int &chance)
{
	if ((rand() % 100) < chance)
		chance = 1;
	else
		chance = 0;
	return (target);
}

bool MeleeCheck(Character *character, Character *target, t_Ability *ability)
{
	int chance = GetChance(character, target, ability);
	if (rand() % 100 < chance)
		return (true);
	return (false);
}

bool RangeCheckWithoutBlockers(Character *character, Character *target, t_Ability *ability)
{
	int chance = GetChance(character, target, ability);
	if (rand() % 100 < chance)
		return (true);
	return (false);
}

static int GetStatusChance(t_Ability *ability, Character *character)
{
	int chance = 0;
	if (ability->type == AXE_JUMP || ability->type == AXE_SLASH)
	{
		for (int i = 0; i < character->abilities.size(); i++)
		{
			if (character->abilities[i].type == TOXIC_BLADE)
			{
				t_ToxicBlade *used = (t_ToxicBlade*)character->abilities[i].stats;
				return (used->hitChance);
			}
		}
	}
	switch (ability->statType)
	{
		case StatStructs::ATTACK_AND_DEBUFF:
		{
			t_AttackWithDebuff *used = (t_AttackWithDebuff*)ability->stats;
			chance = used->debuffChance;
			return (chance);
		}
		case StatStructs::HOST_EYES:
		{
			t_HostEyes *used = (t_HostEyes*)ability->stats;
			chance = used->enemyChance;
			return (chance);
		}
		case StatStructs::BOMB_STRUCT:
		{
			t_DamageBomb *used = (t_DamageBomb*)ability->stats;
			chance = used->statusChance;
			return (chance);
		}
		case StatStructs::SLOW_BOMB_STRUCT:
		{
			t_SlowBomb *used = (t_SlowBomb*)ability->stats;
			chance = used->chance;
			return (chance);
		}
		case StatStructs::ATTACK_WITH_STATUS:
		{
			t_AttackWithStatus *used = (t_AttackWithStatus*)ability->stats;
			chance = used->statusChance;
			return (chance);
		}
		case StatStructs::SHIELD_BASH_STRUCT:
		{
			t_ShieldBash *used = (t_ShieldBash*)ability->stats;
			chance = used->stunChance;
			return (chance);
		}
		case StatStructs::ACID_RAIN_STRUCT:
		{
			t_AcidRainDamage *used = (t_AcidRainDamage*)ability->stats;
			chance = used->chance;
			return (chance);
		}
	}
	return (chance);
}

bool StatusApply(t_Ability *ability, Character *character, Character *target, bool skipCheck)
{
	if (ability == NULL)
		return (false);
	if (ability->statusSign == (-1) && !skipCheck)
		return (false);
	int chance = GetStatusChance(ability, character);
	if (chance == 200)
		return (true);
	if (chance > 95)
		chance = 95;
	if (chance < 5)
		chance = 5;
	int hit = rand() % 100;
	if (hit < chance)
		return (true);
	return (false);
}

static int getMoveChance(t_Ability *ability)
{
	switch (ability->statType)
	{
		case StatStructs::SHIELD_BASH_STRUCT:
		{
			t_ShieldBash *used = (t_ShieldBash*)ability->stats;
			return (used->moveChance);
		}
	}
	return (0);
}

bool MoveChanceCheck(t_Ability *ability, Character *character, Character *target)
{
	int cSize = character->stats.size;
	int tSize = character->stats.size;
	int diff = cSize - tSize;
	int defaultChance = getMoveChance(ability);
	if (defaultChance >= 200)
		return (true);
	if (defaultChance > 95)
		defaultChance = 95;
	if (defaultChance < 5)
		defaultChance = 5;
	int chance = defaultChance + (diff * 6);
	int hit = rand() % 100;
	if (hit < chance)
		return (true);
	return (false);
}
