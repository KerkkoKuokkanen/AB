
#include "../../../hdr/global.h"

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

static bool ValidPos(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	return (true);
}

static float GetControllerScore(t_AiCharacter *character, t_AiMapUnit **map, SDL_Point pos)
{
	if (map[pos.y][pos.x].adds.phantom.isIt)
		return (0.4f);
	int cHealth = character->armor + character->health;
	int tHealth = map[pos.y][pos.x].character->health + map[pos.y][pos.x].character->armor;
	float add = 0.0f;
	if (tHealth > cHealth)
		return (0.4f);
	float scale = 0.4f / (float)cHealth;
	float amount = scale * (float)tHealth;
	return (amount);
}

static float IndividualControlledScore(t_AiCharacter *character, t_AiMapUnit **map)
{
	SDL_Point start = character->position;
	int left = AiGetXToLeft(start);
	int right = AiGetXToRight(start);
	SDL_Point CeckPos[4] = {{left, start.y - 1}, {left, start.y + 1},
							{right, start.y -1}, {right, start.y + 1}};
	float score = 0.0f;
	for (int i = 0; i < 4; i++)
	{
		SDL_Point pos = CeckPos[i];
		if (!ValidPos(pos) || map[pos.y][pos.x].character == NULL)
			continue ;
		score += GetControllerScore(character, map, pos);
	}
	return ((score > 1.0f) ? 1.0f : score);
}

static float IndividualMapEffectsScore(t_AiCharacter *character, t_AiMapUnit **map, float controlScore)
{
	SDL_Point pos = character->position;
	if (map[pos.y][pos.x].adds.smoke.isIt == false)
		return (0.0f);
	if (controlScore == 0.0f)
		return (0.1f);
	float scale = 0.9f / 1.0f;
	float amount = scale * controlScore;
	float score = amount + 0.2f;
	return ((score > 1.0f) ? 1.0f : score);
}

float GetAiPositionScore(std::vector<t_AiCharacter*> &CQ, t_AiMapUnit **map)
{
	float allyScore = 0.0f;
	float enemyScore = 0.0f;
	float allyScoreEffect = 0.0f;
	float enemyScoreEffect = 0.0f;
	int eAmount = 0, aAmount = 0;
	for (int i = 0; i < CQ.size(); i++)
	{
		float single = IndividualControlledScore(CQ[i], map);
		float effect = IndividualMapEffectsScore(CQ[i], map, single);
		if (CQ[i]->character->ally)
		{
			allyScore += single;
			allyScoreEffect += effect;
			aAmount += 1;
		}
		else
		{
			enemyScore += single;
			enemyScoreEffect += effect;
			eAmount += 1;
		}
	}
	float eHScore = (enemyScore + (float)eAmount) / (float)(eAmount + aAmount);
	float aHScore = (allyScore + (float)aAmount) / (float)(eAmount + aAmount);
	float eHScoreEff = (enemyScoreEffect + (float)eAmount) / (float)(eAmount + aAmount);
	float aHScoreEff = (allyScoreEffect + (float)aAmount) / (float)(eAmount + aAmount);
	float beeh = eHScore - aHScore;
	float baah = eHScoreEff - aHScoreEff;
	beeh *= 1.2f;
	baah *= 1.2f;
	return (beeh + baah);
}
