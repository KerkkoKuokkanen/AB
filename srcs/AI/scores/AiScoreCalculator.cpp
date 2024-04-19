#include "../../../hdr/global.h"
#define MOVE_DIVIDER 1.0f
#define CONVENTIONAL_MOVE_DIVIDER 1.0f
#define BIG_NUMBER 9999999
#define FULL_BLOCK_MULTI 0.02f
#define SCALED_MAX_WORTH 110.0f
#define SCALED_WORTH_ENEMY_MULTI 0.2f
#define UNIT_SCORE 1000.0f
#define CONTROLLED_SMOKE_SCORE 19.0f
#define SMOKE_SCORE 3.0f

static std::vector<t_AiCharacter*> charQ;
static std::vector<t_AiCharacter*> saves;

int AiGetXToRight(SDL_Point pos)
{
	int modder = (pos.y % 2 == 0) ? 0 : 1;
	return (pos.x + modder);
}

int AiGetXToLeft(SDL_Point pos)
{
	int modder = (pos.y % 2 == 0) ? -1 : 0;
	return (pos.x + modder);
}

bool AiValidPos(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	return (true);
}

static bool IsCharacter(t_AiMapUnit &point)
{
	if (point.character == NULL)
		return (false);
	return (true);
}

static void SetUpCharQ(t_AiMapUnit **map)
{
	int w = gameState.battle.ground->map[0].size();
	int h = gameState.battle.ground->map.size();
	charQ.clear();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			bool value = IsCharacter(map[i][j]);
			if (value == false)
				continue ;
			charQ.push_back(map[i][j].character);
		}
	}
	OrderTheCharQ(charQ);
	RemoveTheDead(map, charQ);
}

static float GetTheDistForMeleePosition(SDL_Point targPos, SDL_Point charPos, t_AiMapUnit **map)
{
	int xLeft = AiGetXToLeft(targPos);
	int xRight = AiGetXToRight(targPos);
	SDL_Point positions[4] = {{xRight, targPos.y - 1}, {xRight, targPos.y + 1},
								{xLeft, targPos.y - 1}, {xLeft, targPos.y + 1}};
	SDL_Point distBlocks[4] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
	int shortest = BIG_NUMBER;
	int shortestReal = BIG_NUMBER;
	int blockCount = 0;
	for (int i = 0; i < 4; i++)
	{
		if (!AiValidPos(positions[i]))
			continue ;
		int dist = moveMaps.abilities[charPos.y][charPos.x].map[positions[i].y][positions[i].x];
		distBlocks[i].x = dist;
		if (dist < shortest)
			shortest = dist;
		if (map[positions[i].y][positions[i].x].blocked)
			distBlocks[i].y = (-1);
		else
		{
			distBlocks[i].y = 1;
			if (dist < shortestReal)
				shortestReal = dist;
		}
	}
	if (shortestReal == shortest)
		return ((float)shortest);
	if (shortestReal == BIG_NUMBER)
		return (moveMaps.abilities[charPos.y][charPos.x].map[targPos.y][targPos.x] * FULL_BLOCK_MULTI);
	for (int i = 0; i < 4; i++)
	{
		if (distBlocks[i].x == (-1) && blockCount == 0)
			blockCount++;
		if (distBlocks[i].x < shortestReal)
			blockCount++;
	}
	float shortMulti = 1.0f - (((float)blockCount * 2.25f) / 10.0f);
	return ((float)shortestReal * shortMulti);
}

static float GetCharDistScoreMelee(t_AiCharacter *charac, t_AiMapUnit **map)
{
	float score = 0.0f;
	float minDist = BIG_NUMBER;
	int index = 0;
	SDL_Point targ = charac->position;
	for (int i = 0; i < charQ.size(); i++)
	{
		if (charQ[i]->character->ally)
		{
			float dist = GetTheDistForMeleePosition(charQ[i]->position, targ, map);
			if (dist <= 0.000001)
				continue ;
			float test = dist / MOVE_DIVIDER;
			if (test < minDist)
			{
				index = i;
				minDist = test;
			}
			score += test;
		}
	}
	if (minDist > (BIG_NUMBER - 10.0f))
		return (score);
	score += (minDist * 2.0f);
	return (score);
}

static float DistanceScore(t_AiMapUnit **map)
{
	float score = 0.0f;
	for (int i = 0; i < charQ.size(); i++)
	{
		if (charQ[i]->character->ally == false)
			score += GetCharDistScoreMelee(charQ[i], map);
	}
	return (score);
}

static float CheckSmokeForAi(t_AiMapUnit **map, SDL_Point pos)
{
	if (map[pos.y][pos.x].adds.smoke.isIt == false)
		return (0.0f);
	int left = AiGetXToLeft(pos);
	int right = AiGetXToRight(pos);
	SDL_Point posses[4] = {{left, pos.y + 1}, {left, pos.y - 1}, {right, pos.y + 1}, {right, pos.y - 1}};
	for (int i = 0; i < 4; i++)
	{
		if (!AiValidPos(posses[i]))
			continue ;
		if (map[posses[i].y][posses[i].x].character != NULL &&
			map[posses[i].y][posses[i].x].character->character->ally)
			return (CONTROLLED_SMOKE_SCORE);
	}
	return (SMOKE_SCORE);
}

static float SmokeSore(t_AiMapUnit **map)
{
	float ret = 0.0f;
	for (int i = 0; i < charQ.size(); i++)
	{
		if (charQ[i]->character->ally == true)
			continue ;
		ret += CheckSmokeForAi(map, charQ[i]->position);
	}
	return (ret);
}

static SDL_Point GetScaleMaxes(std::vector<t_AiCharacter*> &charQ)
{
	int maxAlly = 0;
	int maxEnemy = 0;
	for (int i = 0; i < charQ.size(); i++)
	{
		t_AiCharacter *character = charQ[i];
		if (character->alive == false)
			continue ;
		int amount = character->character->stats.maxArmor + character->character->stats.maxHealth;
		if (character->character->ally)
		{
			if (amount > maxAlly)
				maxAlly = amount;
		}
		else
		{
			if (amount > maxEnemy)
				maxEnemy = amount;
		}
	}
	SDL_Point ret = {maxAlly, maxEnemy};
	return (ret);
}

static float GetHealthScores(std::vector<t_AiCharacter*> &charQ)
{
	SDL_Point ret = GetScaleMaxes(charQ);
	float ally = (float)ret.x;
	float enem = (float)ret.y;
	float aScore = 0.0f;
	float eScore = 0.0f;
	for (int i = 0; i < charQ.size(); i++)
	{
		t_AiCharacter *targ = charQ[i];
		float scale = 1.0f / (float)(targ->character->stats.maxArmor + targ->character->stats.maxHealth);
		float amount = scale * (float)(targ->health + targ->armor);
		if (targ->character->ally)
		{
			aScore += amount * ally;
			aScore += (float)(targ->health + targ->armor);
			aScore += UNIT_SCORE;
		}
		else
		{
			eScore += amount * enem;
			eScore += (float)(targ->health + targ->armor);
			eScore += UNIT_SCORE;
		}
	}
	return (aScore - eScore);
}

float GetAiScore(t_AiMapUnit **map, bool ally)
{
	SetUpCharQ(map);
	float healthScore = GetHealthScores(charQ);
	float crazyLoopScore = CrazyLoopScore(GetReplica(map), charQ);
	static float best = 9999.0f;
	static SDL_Point bestSave = {0, 0};
	return (healthScore + crazyLoopScore);
}
