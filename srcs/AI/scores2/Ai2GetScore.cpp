
#include "../../../hdr/global.h"
#define UNIT_SCORE 1000.0f

static SDL_Point GetItemScaleMaxes(t_AiMapItem **items)
{
	int maxAlly = 0;
	int maxEnemy = 0;
	for (int i = 0; items[i] != NULL ; i++)
	{
		if (items[i]->own == NULL)
			continue ;
		t_AiCharacter *character = items[i]->own;
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

static SDL_Point GetScaleMaxes(t_AiCharacter **charQ)
{
	int maxAlly = 0;
	int maxEnemy = 0;
	for (int i = 0; charQ[i] != NULL ; i++)
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

static float GetHealthScores(t_AiCharacter **charQ)
{
	SDL_Point ret = GetScaleMaxes(charQ);
	float ally = (float)ret.x;
	float enem = (float)ret.y;
	float aScore = 0.0f;
	float eScore = 0.0f;
	for (int i = 0; charQ[i] != NULL ; i++)
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

static float GetItemHealthScores(t_AiMapItem **items)
{
	SDL_Point ret = GetItemScaleMaxes(items);
	float ally = (float)ret.x;
	float enem = (float)ret.y;
	float allyScore = 0.0f;
	float enemyScore = 0.0f;
	for (int i = 0; items[i] != NULL; i++)
	{
		if (items[i]->own == NULL)
			continue ;
		t_AiCharacter *curr = items[i]->own;
		float scale = 1.0f / (float)(curr->character->stats.maxArmor + curr->character->stats.maxHealth);
		float amount = scale * (float)(curr->health + curr->armor);
		if (curr->character->ally)
		{
			allyScore += amount * ally;
			allyScore += (float)(curr->armor + curr->health);
			allyScore += UNIT_SCORE / 100.0f;
		}
		else
		{
			enemyScore += amount * ally;
			enemyScore += (float)(curr->armor + curr->health);
			enemyScore += UNIT_SCORE / 100.0f;
		}
	}
	return (allyScore - enemyScore);
}

float GetAiS2core(t_AiCharacter *current, t_AiCharacter **charQ, t_AiMapItem **items)
{
	float healthScore = GetHealthScores(charQ); //0.000200
	float crazyLoopScore = CrazyLoop2Score(current, charQ, items); //183.236400
	float itemHealthScore = GetItemHealthScores(items);
	return (healthScore + crazyLoopScore + itemHealthScore);
}
