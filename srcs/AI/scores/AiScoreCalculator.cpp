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
			aScore += (float)targ->moves / 10.0f;
		}
		else
		{
			eScore += amount * enem;
			eScore += (float)(targ->health + targ->armor);
			eScore += UNIT_SCORE;
			eScore += (float)targ->moves / 10.0f;
		}
	}
	return (aScore - eScore);
}

float GetAiScore(t_AiMapUnit **map, t_AiCharacter *current)
{
	SetUpCharQ(map);
	float healthScore = GetHealthScores(charQ);
	float crazyLoopScore = CrazyLoopScore(GetReplica(map), charQ);
	return (healthScore + crazyLoopScore);
}
