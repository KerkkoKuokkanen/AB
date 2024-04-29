
#include "../../../hdr/global.h"
#define TEST_STANDARD 1000000

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

SDL_Point Ai2GetNextSmalles(uint16_t **map, SDL_Point pos)
{
	int left = Ai2GetXToLeft(pos);
	int right = Ai2GetXToRight(pos);
	uint16_t current = map[pos.y][pos.x];
	SDL_Point retPos = pos;
	SDL_Point positions[4] = {{left, pos.y + 1}, {left, pos.y - 1}, {right, pos.y + 1}, {right, pos.y - 1}};
	for (uint8_t i = 0; i < 4; i++)
	{
		if (Ai2ValidPos(positions[i]) == false)
			continue ;
		uint16_t value = map[positions[i].y][positions[i].x];
		if (value < current)
		{
			current = value;
			retPos = positions[i];
		}
	}
	return (retPos);
}

static int GetFatiqueCost(uint16_t **map, SDL_Point start, SDL_Point next)
{
	uint16_t startCost = map[start.y][start.x];
	uint16_t nextCost = map[next.y][next.x];
	uint16_t multi = startCost - nextCost;
	int retValue = (int)((float)multi * 1.5f);
	return (retValue);
}

static bool Ai2PositionIsSmoked(SDL_Point pos, t_AiMapItem **items)
{
	for (uint8_t i = 0; items[i] != NULL; i++)
	{
		if (items[i]->type != SMOKE_BOMB)
			continue ;
		if (items[i]->position.x == pos.x && items[i]->position.y == pos.y)
			return (true);
	}
	return (false);
}

static float Ai2GetOppChance(SDL_Point comparePos, t_AiCharacter *character, t_AiCharacter **charQ, t_AiMapItem **items)
{
	float chanceForHit = 1.0f;
	bool ally = character->character->ally;
	for (int i = 0; charQ[i] != NULL ; i++)
	{
		if (charQ[i]->character->ally == ally)
			continue ;
		SDL_Point pos = charQ[i]->position;
		int distance = moveMaps.staticMoves[pos.y][pos.x].map[comparePos.y][comparePos.x];
		if (distance > 2 || Ai2PositionIsSmoked(pos, items))
			continue ;
		int chance = Ai2GetChance(charQ[i], character, NULL, items);
		float chancer = (float)chance / 100.0f;
		chanceForHit *= (1.0f - chancer);
	}
	for (int i = 0; items[i] != NULL; i++)
	{
		if (items[i]->type != PHANTOM_KNIGHT)
			continue ;
		PhantomKnight *used = (PhantomKnight*)items[i]->item;
		SDL_Point pos = used->position;
		int distance = moveMaps.staticMoves[pos.y][pos.x].map[comparePos.y][comparePos.x];
		if (distance > 2 || Ai2PositionIsSmoked(pos, items))
			continue ;
		int chance = Ai2GetChance(items[i]->own, character, NULL, items);
		float chancer = (float)chance / 100.0f;
		chanceForHit *= (1.0f - chancer);
	}
	chanceForHit = 1.0f - chanceForHit;
	return (chanceForHit);
}

static int GetAi2PosOpportunityDamage(t_AiCharacter *character, t_AiCharacter **charQ, t_AiMapItem **items, SDL_Point comparePos, float chance)
{
	float chanceForHit = chance;
	bool ally = character->character->ally;
	float totalDamage = 0.0f;
	for (int i = 0; charQ[i] != NULL; i++)
	{
		if (charQ[i]->character->ally == ally)
			continue ;
		SDL_Point pos = charQ[i]->position;
		int distance = moveMaps.staticMoves[pos.y][pos.x].map[comparePos.y][comparePos.x];
		if (distance > 2 || Ai2PositionIsSmoked(pos, items))
			continue ;
		int damage = AiOppDamageNumber(character, charQ[i]);
		totalDamage += (float)damage * chanceForHit;
	}
	for (int i = 0; items[i] != NULL; i++)
	{
		if (items[i]->type != PHANTOM_KNIGHT)
			continue ;
		PhantomKnight *used = (PhantomKnight*)items[i]->item;
		SDL_Point pos = used->position;
		int distance = moveMaps.staticMoves[pos.y][pos.x].map[comparePos.y][comparePos.x];
		if (distance > 2 || Ai2PositionIsSmoked(pos, items))
			continue ;
		int damage = AiOppDamageNumber(character, items[i]->own);
		totalDamage += (float)damage * chanceForHit;
	}
	return ((int)totalDamage);
}

static int GetExtraEnergyNeeded(float hitChance)
{
	if (hitChance > 0.91)
		return (3);
	if (hitChance > 0.81)
		return (2);
	if (hitChance > 0.51)
		return (1);
	return (0);
}

static float GetMoveScore(SDL_Point pos, int fatCost, int dmgCost, int eeCost, t_AiCharacter *current, t_AiCharacter **charQ, t_AiMapItem **items)
{
	SDL_Point curPos = current->position;
	int currArmor = current->armor;
	int currHealth = current->health;
	int currFat = current->fatigue;
	int currMoves = current->moves;
	CreateDamageToAiCharacter(current, dmgCost); //0.219400
	current->position = pos;
	current->moves -= eeCost;
	current->fatigue += fatCost;
	float score = GetAiS2core(current, charQ, items); //183.236200
	current->armor = currArmor;
	current->health = currHealth;
	current->fatigue = currFat;
	current->moves = currMoves;
	current->position = curPos;
	return (score);
}

void AiIterator2::MoveToPosition(uint8_t x, uint8_t y)
{
	if (movables[y][x] == TOOL_MAP_SIGN
		|| movables[y][x] == TOOL_MAP_BLOCKER)
		return ;
	SDL_Point goal = current->position;
	SDL_Point start = {(int)x, (int)y};
	int fatiqueCost = 0;
	int damageRecieved = 0;
	int extraEnergyUsed = 0;
	int maxUsableFatique = current->character->stats.maxFatigue - current->fatigue;
	int maxUsableHealth = current->armor + current->health;
	int maxUsableExtraEnergy = current->moves - movables[y][x];
	while (!(start.x == goal.x && start.y == goal.y))
	{
		SDL_Point next = Ai2GetNextSmalles(movables, start); //0.000100
		fatiqueCost += GetFatiqueCost(movables, start, next); //0.000100
		if (fatiqueCost > maxUsableFatique)
			return ;
		float oppChance = Ai2GetOppChance(next, current, charQ, mapItems); //1.243000
		extraEnergyUsed += GetExtraEnergyNeeded(oppChance); //0.000100
		if (extraEnergyUsed > maxUsableExtraEnergy)
			return ;
		damageRecieved += GetAi2PosOpportunityDamage(current, charQ, mapItems, next, oppChance); //1.220000
		if (damageRecieved > maxUsableHealth)
			return ;
		start = next;
	}
	int energyCost = extraEnergyUsed + movables[y][x];
	float score = GetMoveScore({x, y}, fatiqueCost, damageRecieved, energyCost, current, charQ, mapItems); //192.222500
	AddToTheAiMoves(savedMoves[size - 1], {{x, y}, 0, score}, ally); //0.313400 firstTime 149.766500
}

/* DeltaTimeStart();
	for (int i = 0; i < 1000000; i++)
	{
		float score = GetMoveScore({x, y}, fatiqueCost, damageRecieved, energyCost, current, charQ, mapItems);
		blastFurnace += i;
	}
	DeltaTimeGet(); */


//Idis: What if there was an overworld map on the game and a hud in the center. Every time a hero dies it respawns at the center
