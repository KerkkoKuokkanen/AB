
#include "../../../hdr/global.h"
#define DEFAULT_ENERGY_AMOUNT 10
#define BIG_MINUS -99999.9
#define SEARCH_NUMBER 50

uint16_t **moveMap = NULL;
uint8_t gameWidthhh = 0;
uint8_t gameHeighttt = 0;

void InitCrazyLoopForIteration()
{
	moveMap = CreateMoveMapForAi2();
	int w = gameState.battle.ground->map[0].size();
	int h = gameState.battle.ground->map.size();
	gameWidthhh = (uint8_t)w;
	gameHeighttt = (uint8_t)h;
}

void EndCrazyLoopIteration()
{
	DestroyMoveMap2(moveMap);
}

static int Ai2GetXToRight(SDL_Point pos)
{
	int modder = (pos.y % 2 == 0) ? 0 : 1;
	return (pos.x + modder);
}

static int Ai2GetXToLeft(SDL_Point pos)
{
	int modder = (pos.y % 2 == 0) ? -1 : 0;
	return (pos.x + modder);
}

static bool Ai2ValidPos(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	return (true);
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
		SDL_Point nextNext = Ai2GetNextSmalles(map, next);
		if (next.x == nextNext.x && next.y == nextNext.y)
			return (SEARCH_NUMBER);
		int distanceToStart = map[next.y][next.x];
		int currDistance = AiDistBetweenPositions(next, targetPos);
		if (currDistance >= distance)
			break ;
		next = nextNext;
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

static void Ai2IterMoveMap(uint16_t **moveMap, int moves, int targetMoves, SDL_Point pos)
{
	int left = Ai2GetXToLeft(pos);
	int right = Ai2GetXToRight(pos);
	int currentHeight = gameState.battle.ground->map[pos.y][pos.x].height;
	SDL_Point positions[4] = {{left, pos.y + 1}, {left, pos.y - 1}, {right, pos.y + 1}, {right, pos.y - 1}};
	for (uint8_t i = 0; i < 4; i++)
	{
		if (Ai2ValidPos(positions[i]) == false)
			continue ;
		if (moveMap[positions[i].y][positions[i].x] == TOOL_MAP_BLOCKER)
			continue ;
		int plus = 2;
		int height = gameState.battle.ground->map[positions[i].y][positions[i].x].height;
		if (height > currentHeight)
			plus = (2 + (height - currentHeight));
		else if (height < currentHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= targetMoves)
		{
			if (moveMap[positions[i].y][positions[i].x] > temp)
			{
				moveMap[positions[i].y][positions[i].x] = temp;
				Ai2IterMoveMap(moveMap, temp, targetMoves, positions[i]);
			}
		}
	}
}

static bool CheckIfPositionBlocked(SDL_Point pos, t_AiCharacter **charQ, t_AiMapItem **items)
{
	t_GMU *used = &gameState.battle.ground->map[pos.y][pos.x];
	if (used->obj != NULL && used->blocked)
		return (true);
	for (int i = 0; charQ[i] != NULL; i++)
	{
		if (charQ[i]->position.x == pos.x && charQ[i]->position.y == pos.y)
			return (true);
	}
	for (int i = 0; items[i] != NULL; i++)
	{
		if (items[i]->type == SMOKE_BOMB)
			continue ;
		if (items[i]->position.x == pos.x && items[i]->position.y == pos.y)
			return (true);
	}
	return (false);
}

static void GetAi22MapMovables(uint16_t **moveMap, SDL_Point pos, int moves, t_AiCharacter **charQ, t_AiMapItem **items)
{
	for (uint8_t i = 0; i < gameHeighttt; i++)
	{
		for (uint8_t j = 0; j < gameWidthhh; j++)
		{
			moveMap[i][j] = TOOL_MAP_SIGN;
			if (CheckIfPositionBlocked({j, i}, charQ, items))
				moveMap[i][j] = TOOL_MAP_BLOCKER;
		}
	}
	moveMap[pos.y][pos.x] = 0;
	Ai2IterMoveMap(moveMap, moves, moves, pos);
}

static float GetPositionScoresForCharacters(t_AiCharacter *current, t_AiCharacter **charQ, t_AiMapItem **items)
{
	float allyOffence = 0.0f;
	float enemyOffence = 0.0f;
	for (int i = 0; charQ[i] != NULL ; i++)
	{
		GetAi22MapMovables(moveMap, charQ[i]->position, SEARCH_NUMBER, charQ, items);
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
