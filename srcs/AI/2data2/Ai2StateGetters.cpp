
#include "../../../hdr/global.h"

static t_AiCharacter *GetTargetForMelee(t_Ai2State *current, SDL_Point pos)
{
	t_AiCharacter *ret = NULL;
	for (int i = 0; current->charQ[i] != NULL; i++)
	{
		SDL_Point check = current->charQ[i]->position;
		if (check.x == pos.x && check.y == pos.y)
			return (current->charQ[i]);
	}
	for (int i = 0; current->items[i] != NULL; i++)
	{
		if (current->items[i]->own == NULL)
			continue ;
		SDL_Point check = current->items[i]->position;
		if (check.x == pos.x && check.y == pos.y)
			return (current->items[i]->own);
	}
	return (ret);
}

static bool AiCharHasTheJuice(t_AiCharacter *current, t_Ability *ability)
{
	int cost = ability->cost;
	int moves = current->moves;
	if (cost > moves)
		return (false);
	int remainingFat = current->character->stats.maxFatigue - current->fatigue;
	int fatCost = ability->fatigue;
	if (fatCost > remainingFat)
		return (false);
	return (true);
}

static int GetAi2CharQSize(t_AiCharacter **charQ)
{
	int count = 0;
	while (charQ[count] != NULL)
		count++;
	return (count);
}

static int GetAi2ItmsSize(t_AiMapItem **items)
{
	int count = 0;
	while (items[count] != NULL)
		count++;
	return (count);
}

static void AllocateSizeToSetted(t_Ai2State *current, t_Ai2State *setted, t_AiCharacter *turn, t_AiCharacter *damaged)
{
	int size1 = GetAi2CharQSize(current->charQ);
	int size2 = GetAi2ItmsSize(current->items);
	if (damaged->alive == false)
	{
		int cSing = damaged->character->cSing;
		if (cSing == PHANTOM_LION || cSing == TOOLS)
			size2 -= 1;
		else
			size1 -= 1;
	}
	setted->charQ = GetAiCharacterArray(size1 + 1);
	setted->items = GetAiMapItemArray(size2 + 1);
}

static void SetTheNewState(t_Ai2State *current, t_Ai2State *setted, t_AiCharacter *turn, t_AiCharacter *damaged)
{
	AllocateSizeToSetted(current, setted, turn, damaged);
	
}

static void SetDamageToTarget(t_Ability *ability, t_Ai2State *current, t_Ai2State *setted, t_AiCharacter *target)
{
	t_AiCharacter *newCurr = GetReplicaAiCharacter(current->current);
	t_AiCharacter *damaged = GetReplicaAiCharacter(target);
	newCurr->moves -= ability->cost;
	newCurr->fatigue += ability->fatigue;
	float chance = Ai2GetChance(newCurr, damaged, ability, current->items);
	int damage = AiDamageNumber(damaged, newCurr, ability);
	damage = (int)((float)damage * (chance / 100.0f));
	CreateDamageToAiCharacter(damaged, damage);
}

t_Ai2State *GetDefaultMeleeState(t_Ability *ability, t_Ai2State *current, t_Ai2State *setted, SDL_Point pos, int abilityUseIndex)
{
	if (abilityUseIndex > 0)
		return (NULL);
	if (AiCharHasTheJuice(current->current, ability) == false)
		return (NULL);
	t_AiCharacter *target = GetTargetForMelee(current, pos);
	if (target == NULL || target->character->ally == current->current->character->ally)
		return (NULL);
	int range = ability->range;
	SDL_Point currPos = current->current->position;
	int distance = moveMaps.staticMoves[currPos.y][currPos.x].map[pos.y][pos.x];
	if (distance > range)
		return (NULL);
	return (NULL);
}
