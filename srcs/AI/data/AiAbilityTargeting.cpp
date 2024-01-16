
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

void CreateDamageToAiCharacter(t_AiCharacter *character, int damage)
{
	int armor = character->armor;
	if (armor >= damage)
	{
		character->armor -= damage;
		return ;
	}
	damage = damage - character->armor;
	character->armor = 0;
	character->health -= damage;
	if (character->health <= 0)
		character->alive = false;
}

static void CreateDamageToPosition(SDL_Point pos, t_AiCharacter *damager, t_Ability *ability, t_AiMapUnit **map)
{
	t_AiCharacter *charm = &map[pos.y][pos.x].character;
	if (charm->character == NULL)
		return ;
	int chance = AiGetChance(damager, charm, ability, map);
	int damage = AiDamageNumber(charm, damager, ability);
	damage = rounding((float)damage * ((float)chance / 100.0f));
	CreateDamageToAiCharacter(charm, damage);
}

static void AddAbilityUseCosts(t_Ability *ability, t_AiMapUnit **map, SDL_Point pos)
{
	t_AiCharacter *character = &map[pos.y][pos.x].character;
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
			CreateDamageToPosition(pos, &character, ability, newMap);
			AddAbilityUseCosts(ability, newMap, pos);
			break ;
		}
		case SMOKE_BOMB:
		{
			t_LastingEffect *smoke = (t_LastingEffect*)ability->stats;
			newMap[pos.y][pos.x].adds.smoke = {true, smoke->turns, character.character};
			break ;
		}
		case DAGGER_SLASH:
		{
			CreateDamageToPosition(pos, &character, ability, newMap);
			AddAbilityUseCosts(ability, newMap, pos);
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
