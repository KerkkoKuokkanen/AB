#include "../../../hdr/global.h"
#define MOVE_DIVIDER 1.0f
#define CONVENTIONAL_MOVE_DIVIDER 1.0f
#define BIG_NUMBER 9999999
#define FULL_BLOCK_MULTI 0.02f
#define SCALED_MAX_WORTH 110.0f
#define SCALED_WORTH_ENEMY_MULTI 0.2f
#define UNIT_SCORE 100.0f
#define CONTROLLED_SMOKE_SCORE 19.0f
#define SMOKE_SCORE 3.0f

static std::vector<t_AiCharacter*> charQ;

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

static bool AiValidPos(SDL_Point pos)
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

static float GetScaledScore(t_AiCharacter *character)
{
	int max = character->character->stats.maxArmor + character->character->stats.maxHealth;
	if (max == 0)
		return (0.0f);
	float unit = SCALED_MAX_WORTH / (float)max;
	float multi = (float)(character->armor + character->health);
	float score = unit * multi;
	if (character->character->ally == false)
		score *= SCALED_WORTH_ENEMY_MULTI;
	return (score);
}

static float GetHealthScore(t_AiMapUnit **map)
{
	float ah = 0.0f;
	float eh = 0.0f;
	float scaledAH = 0.0f;
	float scaledEH = 0.0f;
	int w = gameState.battle.ground->map[0].size();
	int h = gameState.battle.ground->map.size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			bool value = IsCharacter(map[i][j]);
			if (value == false)
				continue ;
			charQ.push_back(map[i][j].character);
			if (map[i][j].character->character->ally)
			{
				if (map[i][j].character->alive)
				{
					ah += (float)(map[i][j].character->health + map[i][j].character->armor);
					scaledAH += GetScaledScore(map[i][j].character);
				}
			}
			else
			{
				if (map[i][j].character->alive)
				{
					eh += (float)(map[i][j].character->health + map[i][j].character->armor);
					scaledEH += GetScaledScore(map[i][j].character);
				}
			}
		}
	}
	float finalValue = ah - eh + scaledAH - scaledEH;
	return (finalValue);
}

static float UnitScores(t_AiMapUnit **map)
{
	float ally = 0.0f;
	float enem = 0.0f;
	for (int i = 0; i < charQ.size(); i++)
	{
		if (charQ[i]->alive == false)
			continue ;
		if (charQ[i]->character->ally)
			ally += UNIT_SCORE;
		else
			enem += UNIT_SCORE;
	}
	return (ally - enem);
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

float GetAiScore(t_AiMapUnit **map, bool ally)
{
	charQ.clear();
	float healthScore = GetHealthScore(map);
	float unitScore = UnitScores(map);
	float distScore = DistanceScore(map);
	float smokeScore = SmokeSore(map);
	float crazyLoopScore = CrazyLoopScore(map, charQ);
	return (healthScore + unitScore + distScore + smokeScore + crazyLoopScore);
}
