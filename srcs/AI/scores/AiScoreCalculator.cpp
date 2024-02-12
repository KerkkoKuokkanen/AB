#include "../../../hdr/global.h"
#define MOVE_DIVIDER 50.0f

static std::vector<t_AiCharacter*> charQ;

typedef struct s_ValueBlock
{
	float healthVal;
	float fatVal;
}				t_ValueBlock;

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

static float GetHealthScore(t_AiMapUnit **map)
{
	float ah = 0.0f;
	float eh = 0.0f;
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
					ah += (float)(map[i][j].character->health + map[i][j].character->armor);
			}
			else
			{
				if (map[i][j].character->alive)
					eh += (float)(map[i][j].character->health + map[i][j].character->armor);
			}
		}
	}
	float finalValue = ah - eh;
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
			ally += 100.0f;
		else
			enem += 100.0f;
	}
	return (ally - enem);
}

static float GetCharDistScore(t_AiCharacter *charac)
{
	float score = 0.0f;
	SDL_Point targ = charac->position;
	for (int i = 0; i < charQ.size(); i++)
	{
		if (charQ[i]->character->ally)
		{
			SDL_Point check = charQ[i]->position;
			int dist = moveMaps.abilities[targ.y][targ.x].map[check.y][check.x];
			if (dist < 5)
				return (0.0f);
			float test = (float)dist / MOVE_DIVIDER;
			if (score < test)
				score = test;
		}
	}
	return (score);
}

static float DistanceScore(t_AiMapUnit **map)
{
	float score = 0.0f;
	for (int i = 0; i < charQ.size(); i++)
	{
		if (charQ[i]->character->ally == false)
			score += GetCharDistScore(charQ[i]);
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
			return (19.0f);
	}
	return (3.0f);
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
	return (healthScore + unitScore + distScore + smokeScore);
}
