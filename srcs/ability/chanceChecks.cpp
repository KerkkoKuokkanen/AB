
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
	int hit = rand() % 100;
	if (hit < chance)
		return (true);
	return (false);
}
