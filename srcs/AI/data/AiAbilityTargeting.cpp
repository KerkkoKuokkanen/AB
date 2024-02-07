
#include "../../../hdr/global.h"

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
			AdditionalActions(pos, ability, newMap);
			return ;
		}
	}
	SetAbilityToAction(pos, ability, newMap, character->position);
}

void AiIterator::SetAbilityToAction(SDL_Point pos, t_Ability *ability, t_AiMapUnit **newMap, SDL_Point add)
{
	if (!secondLap)
	{
		float score = GetAiScore(newMap, true);
		moveSaves.push_back({iterationLoop, ability->type, score, add});
		return ;
	}
	if (!InSaves(iterationLoop, ability->type, add))
		return ;
	float score = SendToNextOne(newMap, newMap[add.y][add.x].character, moveMoves);
	if (score < action.score)
	{
		action.ability = ability;
		action.pos = pos;
		action.score = score;
		action.same = false;
	}
}
//The ability that is being sent to action in the actual game propably does not have all the nessecary data so fix that!!