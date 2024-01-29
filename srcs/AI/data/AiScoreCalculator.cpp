#include "../../../hdr/global.h"
#define HEALTH_MULTI 1.0f
#define FAT_MULTI 0.3f
#define IND_HEALTH_MULTI 0.8f

static std::vector<t_AiCharacter*> charQ;

typedef struct s_ValueBlock
{
	float healthVal;
	float fatVal;
}				t_ValueBlock;

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
	float totalE = 0.0f;
	float totalA = 0.0f;
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
					totalA = (float)(map[i][j].character->character->stats.health + map[i][j].character->character->stats.armor);
				}
			}
			else
			{
				if (map[i][j].character->alive)
				{
					eh += (float)(map[i][j].character->health + map[i][j].character->armor);
					totalE = (float)(map[i][j].character->character->stats.health + map[i][j].character->character->stats.armor);
				}
			}
		}
	}
	float eUnit = 1.0f / totalE;
	float aUnit = 1.0f / totalA;
	float finalValue = (aUnit * ah) - (eUnit * eh);
	finalValue *= HEALTH_MULTI;
	return (finalValue);
}

static float SingleCharacterHealthScore(t_AiCharacter *character)
{
	int curr = character->health;
	int max = character->character->stats.maxHealth;
	if (curr <= 0)
		return (-1.0f);
	float scale = 1.0f / (float)max;
	float value = scale * (float)(max - curr);
	return (0.5f * (value * value));
}

static float SingleCharacterFatigueScore(t_AiCharacter *character)
{
	int curr = character->fatigue;
	int max = character->character->stats.maxFatigue;
	if (curr <= 0)
		return (0.0f);
	float scale = 1.0f / (float)max;
	float val = scale * (float)curr;
	return (val * val);
}

static SDL_FPoint GetIndividualScores(t_AiMapUnit **map)
{
	t_ValueBlock eVals = {};
	t_ValueBlock aVals = {};
	int eAmount = 0;
	int aAmount = 0;
	for (int i = 0; i < charQ.size(); i++)
	{
		float hVal = SingleCharacterHealthScore(charQ[i]);
		float fVal = SingleCharacterFatigueScore(charQ[i]);
		if (charQ[i]->character->ally)
		{
			aAmount += 1;
			aVals.fatVal += fVal;
			aVals.healthVal += hVal;
		}
		else
		{
			eAmount += 1;
			eVals.fatVal += fVal;
			eVals.healthVal += hVal;
		}
	}
	float eFatScore = eVals.fatVal / (float)eAmount;
	float aFatScore = aVals.fatVal / (float)aAmount;
	float eHScore = (eVals.healthVal + (float)eAmount) / (float)(eAmount + aAmount);
	float aHScore = (aVals.healthVal + (float)aAmount) / (float)(eAmount + aAmount);
	SDL_FPoint ret = {0.0f, 0.0f};
	ret.x = eFatScore - aFatScore;
	ret.y = eHScore - aHScore;
	ret.x *= FAT_MULTI;
	ret.y *= IND_HEALTH_MULTI;
	return (ret);
}

float GetAiScore(t_AiMapUnit **map, bool ally)
{
	charQ.clear();
	float healthScore = GetHealthScore(map);
	SDL_FPoint indEval = GetIndividualScores(map);
	float finalScore = healthScore + indEval.x + indEval.y;
	return (finalScore);
}
