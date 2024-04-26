
#include "../../../hdr/global.h"
#define DEFAULT_ENERGY_AMOUNT 10
#define BIG_MINUS -99999.9

uint16_t **moveMap = NULL;

void InitCrazyLoopForIteration()
{
	moveMap = CreateMoveMapForAi2();
}

void EndCrazyLoopIteration()
{
	DestroyMoveMap2(moveMap);
}

static float AiGetDamageReduction(t_AiCharacter *damager, float damage)
{
	float damageRet = damage;
	float frenzyMulti = (damager->statuses.frenzy == 0) ? 1.0f : 1.55f;
	damageRet *= frenzyMulti;
	return (damageRet);
}

static SDL_FPoint GetBaseDamageAndFatiguePerEnergy(t_AiCharacter *character, t_Ability *ability, t_AiCharacter **charQ, t_AiMapItem **items)
{
	t_Ability *used = ability;
	int cost = (used->cost == 0) ? 1 : used->cost;
	float fatigue = (float)ability->fatigue / (float)cost;
	SDL_FPoint ret = {0.0f, fatigue};
	if (ability->damage == 0)
		return (ret);
	int min = character->character->stats.baseDamageLow;
	int max = character->character->stats.baseDamageHigh;
	float mid = (float)(min + max) / 2.0f;
	float damage = (float)used->damage / 100.0f;
	float expected = ((mid * damage) / (float)cost);
	expected = AiGetDamageReduction(character, expected);
	int chance = AiGetChanceForCharOnly(character, ability, charQ, items);
	float chanceMulti = (float)chance / 100.0f;
	expected *= chanceMulti;
	ret.x = expected;
	return (ret);
}

static int AiDistBetweenPositions(SDL_Point one, SDL_Point two)
{
	return (moveMaps.abilities[one.y][one.x].map[two.y][two.x]);
}

static int TargetPositionDistanceToDistance(uint16_t **map, SDL_Point targetPos, SDL_Point startPos, int distance)
{
	SDL_Point next = targetPos;
	int distanceToStart = map[next.y][next.x];
	if (AiDistBetweenPositions(startPos, targetPos) <= distance)
		return (0);
	while (distanceToStart != 0)
	{
		next = Ai2GetNextSmalles(map, next);
		if (next.x == (-1))
			return (60);
		int distanceToStart = map[next.y][next.x];
		int currDistance = AiDistBetweenPositions(next, targetPos);
		if (currDistance >= distance)
			break ;
	}
	return (map[next.y][next.x]);
}

static float DamageToTargetPosition(SDL_Point target, t_AiCharacter *character, t_Ability *ability, t_AiCharacter **charQ, t_AiMapItem **items, uint16_t **map)
{
	SDL_FPoint damageFatigue = GetBaseDamageAndFatiguePerEnergy(character, ability, charQ, items);
	int distanceToDamage = TargetPositionDistanceToDistance(map, target, character->position, ability->range);
	int damageEnergy = DEFAULT_ENERGY_AMOUNT - distanceToDamage;
	float damageAmount = damageFatigue.x * (float)damageEnergy;
	return (damageAmount);
}

static float GetOffenceScoreForCharacter(t_AiCharacter *character, t_AiCharacter **charQ, t_AiMapItem **items, uint16_t **map)
{
	float offenceScore = 0.0f;
	float currentMax = BIG_MINUS;
	bool ally = character->character->ally;
	for (int i = 0; charQ[i] != NULL ; i++)
	{
		if (charQ[i]->character->ally == ally)
			continue ;
		t_AiCharacter *target = charQ[i];
		for (int j = 0; j < character->character->abilities.size(); j++)
		{
			t_Ability *ability = &character->character->abilities[j];
			if (ability->damage == 0)
				continue ;
			float damage = DamageToTargetPosition(target->position, character, ability, charQ, items, map);
			if (damage > currentMax)
			{
				offenceScore = damage;
				currentMax = damage;
			}
		}
	}
	return (offenceScore);
}

static float GetPositionScoresForCharacters(t_AiCharacter *current, t_AiCharacter **charQ, t_AiMapItem **items)
{
	float allyOffence = 0.0f;
	float enemyOffence = 0.0f;
	for (int i = 0; charQ[i] != NULL ; i++)
	{
		GetAi2MapMovables(moveMap, charQ[i]->position, 50, charQ, items);
		float score = GetOffenceScoreForCharacter(charQ[i], charQ, items, moveMap);
		if (charQ[i]->character->ally)
			allyOffence += score;
		else
			enemyOffence += score;
	}
	allyOffence *= 0.5f;	// modifying these changes alot
	float finalValue = allyOffence - enemyOffence;
	return (finalValue);
}

float CrazyLoop2Score(t_AiCharacter *current, t_AiCharacter **charQ, t_AiMapItem **items)
{
	float ret = GetPositionScoresForCharacters(current, charQ, items);
	return (ret);
}
