
#include "../../../hdr/global.h"

static float GetProtectionMulti(t_AiCharacter *target)
{
	float ret = 1.0f;
	for (int i = 0; i < target->statuses.buffs.size(); i++)
	{
		if (target->statuses.buffs[i].type == BuffTypes::PROTECTION)
			ret -= (float)target->statuses.buffs[i].amount / 100.0f;
	}
	if (ret < 0.1f)
		ret = 0.1f;
	return (ret);
}

static float BurnAddition(t_AiCharacter *target)
{
	int amount = target->statuses.burns.size();
	amount *= 2;
	float multi = 1.0f + ((float)amount / 100.0f);
	return (multi);
}

static float FrenzyAddition(t_AiCharacter *character)
{
	if (character->statuses.frenzy == 0)
		return (1.0f);
	return (1.5f);
}

static int AiGetDamageReduction(t_AiCharacter *damaged, t_AiCharacter *damager, int damage)
{
	float damageRet = (float)damage;
	float burnMulti = BurnAddition(damaged);
	float protectioMulti = GetProtectionMulti(damaged);
	float frenzyMulti = FrenzyAddition(damager);
	damageRet *= burnMulti;
	damageRet *= protectioMulti;
	damageRet *= frenzyMulti;
	return (rounding(damageRet));
}

int AiDamageNumber(t_AiCharacter *target, t_AiCharacter *caster, t_Ability *ability)
{
	int damage = rounding((float)(caster->character->stats.baseDamageLow + caster->character->stats.baseDamageHigh) / 2.0f);
	float abilityMulti = (float)ability->damage / 100.0f;
	damage = rounding((float)damage * abilityMulti);
	damage = AiGetDamageReduction(target, caster, damage);
	return (damage);
}

int AiOppDamageNumber(t_AiCharacter *target, t_AiCharacter *caster)
{
	int damage = rounding((float)(caster->character->stats.baseDamageLow + caster->character->stats.baseDamageHigh) / 2.0f);
	damage = AiGetDamageReduction(target, caster, damage);
	return (damage);
}

t_TargetingType GetAbilityTargetingType(t_Ability *ability)
{
	t_TargetingType ret = {0, 0, false, false, false};
	switch (ability->type)
	{
		case SKELE_MELEE:
			ret = {ability->range, SelectorTypesForAi::SELECTOR, true, true, ability->melee};
			break ;
		case SKELE_LUNGE:
			ret = {ability->range, SelectorTypesForAi::SELECTOR, true, false, ability->melee};
			break ;
		case BIG_THUG_STRIKE:
			ret = {ability->range, SelectorTypesForAi::SELECTOR, true, false, ability->melee};
			break ;
		case THUG_STRIKE:
			ret = {ability->range, SelectorTypesForAi::SELECTOR, true, false, ability->melee};
			break ;
	}
	return (ret);
}
