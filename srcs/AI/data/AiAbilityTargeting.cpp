
#include "../../../hdr/global.h"

void AiIterator::CheckForAbilitySecondTime(SDL_Point pos, int sign)
{
	t_Ability *ability = NULL;
	for (int i = 0; i < character->character->abilities.size(); i++)
	{
		t_Ability *check = &character->character->abilities[i];
		if (check->type == sign)
		{
			ability = check;
			break ;
		}
	}
	HandleAbilityAction(pos, ability);
}

void AiIterator::CheckForAbility(SDL_Point pos)
{
	for (int i = 0; i < character->character->abilities.size(); i++)
	{
		t_Ability *ability = &character->character->abilities[i];
		if ((ability->fatigue + character->fatigue) > character->character->stats.maxFatigue ||
			ability->cost > character->moves || !AiCheckIfCanHit(map, ability, character, pos, character->position))
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
	CheckDeadCharacter(charm, map);
}

static void AddAbilityUseCosts(t_Ability *ability, t_AiMapUnit **map, SDL_Point pos)
{
	t_AiCharacter *character = map[pos.y][pos.x].character;
	character->fatigue += ability->fatigue;
	character->moves -= ability->cost;
}

static void AddBigThugInspireFrenzy(t_AiMapUnit **map, SDL_Point characterPos, t_Ability *ability)
{
	int range = ability->range;
	t_BuffDebuff *used = (t_BuffDebuff*)ability->stats;
	int turns = used->turns;
	int w = gameState.battle.ground->map[0].size();
	int h = gameState.battle.ground->map.size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (map[i][j].character == NULL)
				continue ;
			if (map[i][j].character->character->cSing != THUG)
				continue ;
			map[i][j].character->statuses.frenzy = turns;
		}
	}
}

void AiIterator::UseTheAbility(SDL_Point pos, t_Ability *ability, t_AiMapUnit **newMap)
{
	int sign = ability->type;
	switch (sign)
	{
		case SKELE_MELEE:
		{
			AddAbilityUseCosts(ability, newMap, character->position);
			CreateDamageToPosition(pos, character, ability, newMap);
			break ;
		}
		case SKELE_LUNGE:
		{
			AddAbilityUseCosts(ability, newMap, character->position);
			CreateDamageToPosition(pos, character, ability, newMap);
			AdditionalActions(pos, ability, newMap); //slow one
			return ;
		}
		case BIG_THUG_STRIKE:
		{
			AddAbilityUseCosts(ability, newMap, character->position);
			CreateDamageToPosition(pos, character, ability, newMap);
			break ;
		}
		case THUG_STRIKE:
		{
			AddAbilityUseCosts(ability, newMap, character->position);
			CreateDamageToPosition(pos, character, ability, newMap);
			break ;
		}
		case BIG_THUG_INSPIRE:
		{
			AddAbilityUseCosts(ability, newMap, character->position);
			AddBigThugInspireFrenzy(newMap, character->position, ability);
			break ;
		}
	}
	SetAbilityToAction(pos, ability, newMap, character->position);
}

void AiIterator::SetAbilityToAction(SDL_Point pos, t_Ability *ability, t_AiMapUnit **newMap, SDL_Point add)
{
	if (!secondLap)
	{
		float score = GetAiScore(newMap, newMap[add.y][add.x].character);
		moveSaves.push_back({ability->type, score, add, currentIterPosition});
		return ;
	}
	t_TruthAndScore ret = InSaves(ability->type, add);
	if (ret.isIt == false)
		return ;
	float score = SendToNextOne(newMap, newMap[add.y][add.x].character, moveMoves, ret.score);
	if (score < action.score)
	{
		action.ability = ability;
		action.pos = pos;
		action.score = score;
		action.same = false;
		action.tPoints.push_back(add);
	}
}
