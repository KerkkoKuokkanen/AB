
#include "../../../hdr/global.h"

static int AiGetXToRight(SDL_Point pos)
{
	int modder = (pos.y % 2 == 0) ? 0 : 1;
	return (pos.x + modder);
}

static int AiGetXToLeft(SDL_Point pos)
{
	int modder = (pos.y % 2 == 0) ? -1 : 0;
	return (pos.x + modder);
}

static bool AiValidChecker(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	return (true);
}

static bool CheckForMeleePos(t_AiMapUnit **map, SDL_Point pos, bool ally)
{
	if (!AiValidChecker(pos))
		return (false);
	if (map[pos.y][pos.x].character == NULL)
		return (false);
	if (map[pos.y][pos.x].character->character->ally != ally)
		return (true);
	return (false);
}

static bool CheckForNotMelee(t_AiMapUnit **map, t_Ability *ability, SDL_Point pos, bool ally)
{
	if (ability->melee)
		return (false);
	int left = AiGetXToLeft(pos);
	int right = AiGetXToRight(pos);
	if (CheckForMeleePos(map, {left, pos.y - 1}, ally))
		return (true);
	if (CheckForMeleePos(map, {left, pos.y + 1}, ally))
		return (true);
	if (CheckForMeleePos(map, {right, pos.y - 1}, ally))
		return (true);
	if (CheckForMeleePos(map, {right, pos.y + 1}, ally))
		return (true);
	return (false);
}

static bool CheckIfCanHit(t_AiMapUnit **map, t_Ability *ability, t_AiCharacter *character, SDL_Point pos, SDL_Point start)
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
	if (CheckForNotMelee(map, ability, character->position, character->character->ally))
		return (false);
	if (map[pos.y][pos.x].character != NULL && ret.characters == false)
		return (false);
	if (ret.targetType == SelectorTypesForAi::SELECTOR && map[pos.y][pos.x].character == NULL)
		return (false);
	if (ret.targetType == SelectorTypesForAi::SELECTOR && map[pos.y][pos.x].character->alive == false)
		return (false);
	return (true);
}

void AiIterator::CheckForAbility(SDL_Point pos)
{
	for (int i = 0; i < character->character->abilities.size(); i++)
	{
		t_Ability *ability = &character->character->abilities[i];
		if ((ability->fatigue + character->fatigue) > character->character->stats.maxFatigue ||
			ability->cost > character->moves || !CheckIfCanHit(map, ability, character, pos, character->position))
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

void AiCheckForHosting(t_AiCharacter *character, t_AiMapUnit **map)
{
	if (character->statuses.hosting == NULL)
		return ;
	Character *hosted = (Character*)character->statuses.hosting;
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (map[i][j].character->character == hosted)
			{
				map[i][j].character->statuses.hosted = false;
				character->statuses.hosting = NULL;
				return ;
			}
		}
	}
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

void CheckDeadCharacter(t_AiCharacter *character, t_AiMapUnit **map)
{
	if (character->alive)
		return ;
	if (character->character->cSing != LION && character->character->cSing != THIEF)
		return ;
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (map[i][j].adds.smoke.parent == character->character)
				map[i][j].adds.smoke.parent = NULL;
			if (map[i][j].adds.phantom.parent == character->character)
			{
				map[i][j].adds.phantom.isIt = false;
				map[i][j].adds.phantom.parent = NULL;
				map[i][j].adds.phantom.turns = 0;
			}
		}
	}
}

static void CreateDamageToPosition(SDL_Point pos, t_AiCharacter *damager, t_Ability *ability, t_AiMapUnit **map)
{
	t_AiCharacter *charm = map[pos.y][pos.x].character;
	if (charm->character == NULL)
		return ;
	int chance = AiGetChance(damager, charm, ability, map);
	int damage = AiDamageNumber(charm, damager, ability);
	damage = rounding((float)damage * ((float)chance / 100.0f));
	CreateDamageToAiCharacter(charm, damage);
	AiCheckForHosting(charm, map);
	CheckDeadCharacter(charm, map);
}

static void AddAbilityUseCosts(t_Ability *ability, t_AiMapUnit **map, SDL_Point pos)
{
	t_AiCharacter *character = map[pos.y][pos.x].character;
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
			AddAbilityUseCosts(ability, newMap, character->position);
			CreateDamageToPosition(pos, character, ability, newMap);
			break ;
		}
		case SMOKE_BOMB:
		{
			AddAbilityUseCosts(ability, newMap, character->position);
			t_LastingEffect *smoke = (t_LastingEffect*)ability->stats;
			newMap[pos.y][pos.x].adds.smoke = {true, smoke->turns, character->character};
			break ;
		}
		case DAGGER_SLASH:
		{
			AddAbilityUseCosts(ability, newMap, character->position);
			CreateDamageToPosition(pos, character, ability, newMap);
			break ;
		}
	}
	SetAbilityToAction(pos, ability, newMap);
}

void AiIterator::SetAbilityToAction(SDL_Point pos, t_Ability *ability, t_AiMapUnit **newMap)
{
	float score = SendToNextOne(newMap, character, 0, moveMoves);
	if (character->character->ally)
	{
		if (score > action.score)
		{
			action.ability = ability;
			action.pos = pos;
			action.score = score;
			action.same = false;
		}
	}
	if (score < action.score)
	{
		action.ability = ability;
		action.pos = pos;
		action.score = score;
		action.same = false;
	}
}
