
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

static float AccBuffMulit(Character *character)
{
	float ret = 1.0f;
	for (int i = 0; i < character->statuses.buffs.size(); i++)
	{
		if (character->statuses.buffs[i].type == BuffTypes::ACCURACY)
			ret += (float)character->statuses.buffs[i].amount / 100.0f;
	}
	return (ret);
}

static float AccDeBuffMulti(Character *character)
{
	float ret = 1.0f;
	for (int i = 0; i < character->statuses.deBuffs.size(); i++)
	{
		if (character->statuses.deBuffs[i].type == BuffTypes::ACCURACY)
			ret -= (float)character->statuses.deBuffs[i].amount / 100.0f;
	}
	if (ret < 0.1f)
		ret = 0.1f;
	return (ret);
}

static int ChanceModifiers(Character *character, Character *target, int chance)
{
	float chanceRet = (float)chance;
	float accBuff = AccBuffMulit(character);
	float hostMulti = (character->statuses.hosted) ? 0.85f : 1.0f;
	float accDebuff = AccDeBuffMulti(character);
	chanceRet *= accBuff;
	chanceRet *= accDebuff;
	chanceRet *= hostMulti;
	return (rounding(chanceRet));
}

static int SmokeChecker(Character *character, int chance)
{
	SDL_Point pos = character->position;
	if (!CheckIfSmoked(pos))
		return (chance);
	chance = rounding((float)chance * 0.5f);
	return (chance);
}

static int GetTheBaseChance(Character *character, Character *target, t_Ability *ability)
{
	int baseChance = 0;
	if (ability == NULL)
	{
		baseChance = 50;
		int levelDiff = character->stats.level - target->stats.level;
		baseChance += 5 * levelDiff;
	}
	else
	{
		if (ability->baseChance >= 200)
			return (200);
		baseChance = ability->baseChance;
	}
	return (baseChance);
}

static int CheckOppChancers(Character *character, t_Ability *ability, int ret)
{
	if (ability != NULL)
		return (ret);
	float multi = 1.0f;
	float chanceRet = (float)ret;
	for (int i = 0; i < character->statuses.buffs.size(); i++)
	{
		if (character->statuses.buffs[i].type == BuffTypes::OPPORTUNITY_ACCURACY)
			multi += (float)character->statuses.buffs[i].amount / 100.0f;
	}
	chanceRet *= multi;
	return (rounding(chanceRet));
}

int GetChance(Character *character, Character *target, t_Ability *ability)
{
	int ret = GetTheBaseChance(character, target, ability);
	ret += RangedChance(character, target);
	ret = ChanceModifiers(character, target, ret);
	ret = CheckOppChancers(character, ability, ret);
	ret = (ability == NULL) ? ret : SmokeChecker(character, ret);
	if (ret > 95)
		ret = 95;
	if (ret < 5)
		ret = 5;
	return (ret);
}

bool MeleeCheck(Character *character, Character *target, t_Ability *ability)
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
	int chance = defaultChance + (diff * 6);
	if (defaultChance > 95)
		defaultChance = 95;
	if (defaultChance < 5)
		defaultChance = 5;
	int hit = rand() % 100;
	if (hit < chance)
		return (true);
	return (false);
}
