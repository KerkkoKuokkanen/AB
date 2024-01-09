
#include "../../../hdr/global.h"

static bool CheckIfCanHit(t_AiMapUnit **map, t_Ability *ability, SDL_Point pos, SDL_Point start)
{
	t_TargetingType ret = GetAbilityTargetingType(ability);
	int range = ret.range;
	int dist = 10000;
	if (!ret.staticSearch)
		dist = moveMaps.abilities[start.y][start.x].map[pos.y][pos.x];
	else
		dist = moveMaps.staticMoves[start.y][start.x].map[pos.y][pos.x];
	if (dist > range)
		return (false);
	if (map[pos.y][pos.x].obj.obj == true)
		return (false);
	if (map[pos.y][pos.x].character.character != NULL && ret.characters == false)
		return (false);
	if (ret.targetType == SelectorTypesForAi::SELECTOR && map[pos.y][pos.x].character.character == NULL)
		return (false);
	return (true);
}

void AiIterator::CheckForAbility(SDL_Point pos)
{
	for (int i = 0; i < character.character->abilities.size(); i++)
	{
		t_Ability *ability = &character.character->abilities[i];
		if ((ability->fatigue + character.fatigue) > character.character->stats.maxFatigue ||
			ability->cost > character.moves || !CheckIfCanHit(map, ability, pos, character.position))
			continue ;
		HandleAbilityAction(pos, ability);
	}
}

void AiIterator::HandleAbilityAction(SDL_Point pos, t_Ability *ability)
{
	t_AiMapUnit **newMap = GetReplica(map);
	UseTheAbility(pos, ability, newMap);
	DestroyMap(newMap);
}

static int GetAbilityDamage(t_Ability *ability, Character *character)
{
	int dmg = ability->damage;
	if (dmg == 0)
		return (0);
	int cdMin = character->stats.baseDamageLow;
	int cdMax = character->stats.baseDamageHigh;
	int mid = rounding((float)(cdMax + cdMin) / 2.0f);
	float multi = (float)dmg / 100.0f;
	float amont = (float)mid * multi;
	return (rounding(amont));
}

static void CreateDamageToPosition(SDL_Point pos, Character *damager, t_Ability *ability, t_AiMapUnit **map)
{
	t_AiCharacter *charm = &map[pos.y][pos.x].character;
	if (charm->character == NULL)
		return ;
	int chance = GetChance(damager, charm->character, ability);
	int damage = GetAbilityDamage(ability, damager);
	damage = rounding((float)damage * ((float)chance / 100.0f));
	int armor = charm->armor;
	if (armor >= damage)
	{
		charm->armor -= damage;
		return ;
	}
	damage = damage - charm->armor;
	charm->armor = 0;
	charm->health -= damage;
	if (charm->health <= 0)
		charm->alive = false;
}

static void AddAbilityUseCosts(t_Ability *ability, t_AiCharacter *character)
{
	character->fatigue += ability->fatigue;
	character->moves -= ability->cost;
}

void AiIterator::UseTheAbility(SDL_Point pos, t_Ability *ability, t_AiMapUnit **newMap)
{
	int sign = ability->type;
	switch (sign)
	{
		case DAGGER_THROW:
		{
			CreateDamageToPosition(pos, character.character, ability, newMap);
			AddAbilityUseCosts(ability, &character);
			break ;
		}
		case SMOKE_BOMB:
		{
			t_LastingEffect *smoke = (t_LastingEffect*)ability->stats;
			newMap[pos.y][pos.x].adds.smoke = {true, smoke->turns};
			break ;
		}
		case DAGGER_SLASH:
		{
			CreateDamageToPosition(pos, character.character, ability, newMap);
			AddAbilityUseCosts(ability, &character);
			break ;
		}
	}
	SetAbilityToAction(pos, ability, newMap);
}

void AiIterator::SetAbilityToAction(SDL_Point pos, t_Ability *ability, t_AiMapUnit **newMap)
{
	float score = GetAiScore(newMap, character.character->ally);
	if (score > action.score)
	{
		action.ability = ability;
		action.pos = pos;
		action.score = score;
		action.same = false;
	}
}
