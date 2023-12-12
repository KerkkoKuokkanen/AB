
#include "../../../hdr/global.h"

static int GetTheDamageRandom(Character *character)
{
	int low = character->stats.baseDamageLow;
	int high = character->stats.baseDamageHigh;
	int randRange = high - low;
	int ret = rand() % randRange + low;
	return (ret);
}

static float GetProtectionMulti(Character *target)
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

static float BurnAddition(Character *target)
{
	int amount = target->statuses.burns.size();
	amount *= 2;
	float multi = 1.0f + ((float)amount / 100.0f);
	return (multi);
}

static int GetDamageReduction(Character *damaged, Character *damager, int damage)
{
	float damageRet = (float)damage;
	float burnMulti = BurnAddition(damaged);
	float protectioMulti = GetProtectionMulti(damaged);
	damageRet *= burnMulti;
	damageRet *= protectioMulti;
	return (rounding(damageRet));
}

static SDL_Point GetFinalDamageSplit(Character *target, int damage)
{
	SDL_Point ret = {0, 0};
	int armor = target->stats.armor;
	if (damage <= armor)
	{
		ret.x = damage;
		return (ret);
	}
	int healthDMG = damage - armor;
	ret.x = armor;
	ret.y = healthDMG;
	return (ret);
}

static SDL_Point GetFinalDamageSplitCritical(Character *target, int damage)
{
	SDL_Point ret = {0, 0};
	int armor = target->stats.armor;
	if (damage <= armor)
	{
		ret.x = damage;
		ret.y = damage;
		return (ret);
	}
	int healthDMG = damage + damage - armor;
	ret.x = armor;
	ret.y = healthDMG;
	return (ret);
}

SDL_Point GetOpportunityDamageValues(Character *target, SDL_Point caster)
{
	SDL_Point ret = {0, 0};
	t_GMU *point = &gameState.battle.ground->map[caster.y][caster.x];
	Character *damager = NULL;
	if (point->character != NULL)
		damager = point->character;
	else
	{
		if (point->additional.type == AdditionalObjects::PHANTOM_KNIGHT)
		{
			PhantomKnight *obj = (PhantomKnight*)point->additional.object;
			damager = obj->character;
		}
	}
	if (damager == NULL)
		return (ret);
	int damage = GetTheDamageRandom(damager);
	damage = GetDamageReduction(target, damager, damage);
	return (GetFinalDamageSplit(target, damage));
}

SDL_Point GetDamageValues(Character *target, Character *caster, t_Ability *ability)
{
	int damage = GetTheDamageRandom(caster);
	float abilityMulti = (float)ability->damage / 100.0f;
	damage = rounding((float)damage * abilityMulti);
	damage = GetDamageReduction(target, caster, damage);
	int crit = ability->critChance;
	if (rand() % 100 < crit)
	{
		SetDelayer(6);
		PlaySound(gameState.audio.heartBeat, Channels::VOLUME_45, 0);
		PlaySound(gameState.audio.criticalHit, Channels::VOLUME_36, 0);
		return (GetFinalDamageSplitCritical(target, damage));
	}
	return (GetFinalDamageSplit(target, damage));
}
