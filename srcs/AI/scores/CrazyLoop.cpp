
#include "../../../hdr/global.h"

// (figure out the best way to check the relevant positions)
// -> position scores for character in terms of abilites and their range
// -> position score could for example have three parts like: offence, defence and utility
// (maybe try abilities in the current position MAYBE)
// -> move to different positions in terms of the score
//    if character cant reach these positions move to positions close to the best positions
// -> try abilities in the different positions
// -> final score is health scores and position scores combined

// Position score calcilation ideas:
// Get preferred distances to enemies for characters?
// Give points to positions in terms of how many abilities they can use in thath position
// each ability could have its own simple score giving algorithm in terms of the possible targets
// in positions where you can not use abilities give score in terms of the distance to those good positions
// Give positions defensive score in terms of how long the distance is for the enemies and
// what enemies can use abilities to that position

#define DEFAULT_ENERGY_AMOUNT 10
#define BIG_MINUS -99999.9

static float AiGetDamageReduction(t_AiCharacter *damager, float damage)
{
	float damageRet = damage;
	float frenzyMulti = (damager->statuses.frenzy == 0) ? 1.0f : 1.55f;
	damageRet *= frenzyMulti;
	return (damageRet);
}

static SDL_FPoint GetBaseDamageAndFatiguePerEnergy(t_AiCharacter *character, t_Ability *ability, t_AiMapUnit **map)
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
	int chance = AiGetChanceForCharOnly(character, ability, map);
	float chanceMulti = (float)chance / 100.0f;
	expected *= chanceMulti;
	ret.x = expected;
	return (ret);
}

static SDL_Point GetNextPosition(t_AiMapUnit **map, SDL_Point current)
{
	int left = AiGetXToLeft(current);
	int right = AiGetXToRight(current);
	int y = current.y;
	SDL_Point checks[4] = {{left, y + 1}, {left, y - 1}, {right, y + 1}, {right, y - 1}};
	SDL_Point ret = {-1, -1};
	int dist = TOOL_MAP_SIGN;
	if (dist <= 0)
		return (ret);
	for (int i = 0; i < 4; i++)
	{
		if (AiValidPos(checks[i]) == false)
			continue ;
		int temp = map[checks[i].y][checks[i].x].movable;
		if (temp < dist)
		{
			dist = temp;
			ret = checks[i];
		}
	}
	return (ret);
}

static int AiDistBetweenPositions(SDL_Point one, SDL_Point two)
{
	return (moveMaps.abilities[one.y][one.x].map[two.y][two.x]);
}

static int TargetPositionDistanceToDistance(t_AiMapUnit **map, SDL_Point targetPos, SDL_Point startPos, int distance)
{
	SDL_Point next = targetPos;
	int distanceToStart = map[next.y][next.x].movable;
	if (AiDistBetweenPositions(startPos, targetPos) <= distance)
		return (0);
	while (distanceToStart != 0)
	{
		next = GetNextPosition(map, next);
		if (next.x == (-1))
			return (60);
		int distanceToStart = map[next.y][next.x].movable;
		int currDistance = AiDistBetweenPositions(next, targetPos);
		if (currDistance >= distance)
			break ;
	}
	return (map[next.y][next.x].movable);
}

static float DamageToTargetPosition(t_AiMapUnit **map, SDL_Point target, t_AiCharacter *character, t_Ability *ability)
{
	SDL_FPoint damageFatigue = GetBaseDamageAndFatiguePerEnergy(character, ability, map);
	int distanceToDamage = TargetPositionDistanceToDistance(map, target, character->position, ability->range);
	int damageEnergy = DEFAULT_ENERGY_AMOUNT - distanceToDamage;
	float damageAmount = damageFatigue.x * (float)damageEnergy;
	return (damageAmount);
}

static float GetOffenceScoreForCharacter(t_AiMapUnit **map, t_AiCharacter *character, std::vector<t_AiCharacter*> &charQ)
{
	float offenceScore = 0.0f;
	float currentMax = BIG_MINUS;
	bool ally = character->character->ally;
	for (int i = 0; i < charQ.size(); i++)
	{
		if (charQ[i]->character->ally == ally)
			continue ;
		t_AiCharacter *target = charQ[i];
		for (int j = 0; j < character->character->abilities.size(); j++)
		{
			t_Ability *ability = &character->character->abilities[j];
			if (ability->damage == 0)
				continue ;
			float damage = DamageToTargetPosition(map, target->position, character, ability);
			if (damage > currentMax)
			{
				offenceScore = damage;
				currentMax = damage;
			}
		}
	}
	return (offenceScore);
}

float GetPositionScoresForCharacters(t_AiMapUnit **map, std::vector<t_AiCharacter*> &charQ)
{
	float allyOffence = 0.0f;
	float enemyOffence = 0.0f;
	for (int i = 0; i < charQ.size(); i++)
	{
		findMovablesNormal(map, 60, charQ[i]->position);
		float score = GetOffenceScoreForCharacter(map, charQ[i], charQ);
		if (charQ[i]->character->ally)
			allyOffence += score;
		else
			enemyOffence += score;
	}
	allyOffence *= 0.75f;	// modifying these changes alot
	float finalValue = allyOffence - enemyOffence;
	return (finalValue);
}

//there is something even more broken here
float CrazyLoopScore(t_AiMapUnit **map, std::vector<t_AiCharacter*> &charQ)
{
	float ret = GetPositionScoresForCharacters(map, charQ);
	DestroyMap(map);
	return (ret);
}
