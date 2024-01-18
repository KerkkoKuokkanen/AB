
#include "../../../hdr/global.h"
static SDL_Point GetNextPoint(SDL_Point curr, t_AiMapUnit **map);
static int GetFatigueCost(SDL_Point curr, SDL_Point next, t_AiMapUnit **map);

static bool AtGoal(SDL_Point pos, SDL_Point goal)
{
	if (pos.x == goal.x && pos.y == goal.y)
		return (true);
	return (false);
}

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

static bool AdditionalValidation(SDL_Point pos, t_AiMapUnit **map, bool ally)
{
	if (map[pos.y][pos.x].adds.phantom.isIt == false)
		return (false);
	if (map[pos.y][pos.x].character.character->ally == ally)
		return (false);
	return (true);
}

static bool ValidAttacker(SDL_Point pos, t_AiMapUnit **map, bool ally)
{
	if (AiCheckSmoked(pos, map))
		return (false);
	if (AdditionalValidation(pos, map, ally))
		return (true);
	if (map[pos.y][pos.x].character.character == NULL)
		return (false);
	if (map[pos.y][pos.x].character.alive == false)
		return (false);
	if (map[pos.y][pos.x].character.character->cSing == TOOLS)
		return (false);
	if (map[pos.y][pos.x].character.character->ally == ally)
		return (false);
	if (map[pos.y][pos.x].character.statuses.stun != 0)
		return (false);
	return (true);
}

static bool AiOppExtras(SDL_Point pos, t_AiMapUnit **map, bool ally)
{
	if (AiCheckSmoked(pos, map))
		return (false);
	if (map[pos.y][pos.x].character.character == NULL)
		return (false);
	if (map[pos.y][pos.x].character.alive == false)
		return (false);
	if (map[pos.y][pos.x].character.character->cSing == TOOLS)
		return (false);
	if (map[pos.y][pos.x].character.character->ally == ally)
		return (false);
	if (map[pos.y][pos.x].character.statuses.stun != 0)
		return (false);
	if (map[pos.y][pos.x].character.character->cSing != KNIGHT)
		return (false);
	if (map[pos.y][pos.x].character.statuses.controlZone <= 0)
		return (false);
	return (true);
}

static void GetAiOppDamagers(std::vector<SDL_Point> &dmgs, t_AiMapUnit **map, SDL_Point pos, bool ally)
{
	SDL_Point defs[4] = {
		GetPositionFromCoordinates(pos, {-1, -1}),
		GetPositionFromCoordinates(pos, {-1, 1}),
		GetPositionFromCoordinates(pos, {1, 1}),
		GetPositionFromCoordinates(pos, {1, -1})
	};
	for (int i = 0; i < 4; i++)
	{
		if (AiValidPos(defs[i]))
		{
			if (ValidAttacker(defs[i], map, ally))
				dmgs.push_back(defs[i]);
		}
	}
	SDL_Point extras[8] = {
		GetPositionFromCoordinates(pos, {-2, -2}),
		GetPositionFromCoordinates(pos, {0, -2}),
		GetPositionFromCoordinates(pos, {2, -2}),
		GetPositionFromCoordinates(pos, {1, 0}),
		GetPositionFromCoordinates(pos, {2, 2}),
		GetPositionFromCoordinates(pos, {0, 2}),
		GetPositionFromCoordinates(pos, {-2, 2}),
		GetPositionFromCoordinates(pos, {-1, 0})
	};
	for (int i = 0; i < 8; i++)
	{
		if (AiValidPos(extras[i]))
		{
			if (AiOppExtras(extras[i], map, ally))
				dmgs.push_back(extras[i]);
		}
	}
}

int AiIterator::CheckMovePosition(SDL_Point pos)
{
	std::vector<SDL_Point> damagers;
	GetAiOppDamagers(damagers, map, pos, character.character->ally);
	if (damagers.size() == 0)
		return (0);
	int totalChance = 0;
	float chanceForHit = 1.0f;
	for (int i = 0; i < damagers.size(); i++)
	{
		int chance = GetChance(map[damagers[i].y][damagers[i].x].character.character, character.character, NULL);
		totalChance += chance;
		float chancer = (float)chance / 100.0f;
		chanceForHit *= (1.0f - chancer);
	}
	if (totalChance == 0)
		return (0);
	chanceForHit = 1.0f - chanceForHit;
	float totalDamage = 0.0f;
	for (int i = 0; i < damagers.size(); i++)
	{
		int chance = GetChance(map[damagers[i].y][damagers[i].x].character.character, character.character, NULL);
		float chancer = (float)chance / 100.0f;
		float portion = chancer / (float)totalChance;
		int damage = AiOppDamageNumber(&character, &map[damagers[i].y][damagers[i].x].character);
		totalDamage += ((float)damage * chanceForHit) * portion;
	}
	return (rounding(totalDamage));
}

void AiIterator::HandleMoveAfterMath(SDL_Point target, int damage, int fatigue)
{
	t_AiMapUnit **newMap = GetReplica(map);
	SetDefaultNoCharacter(character.position, newMap);
	SetDefaultCharacter(target, &character, newMap);
	int cost = map[target.y][target.x].movable;
	newMap[target.y][target.x].character.moves -= cost;
	newMap[target.y][target.x].character.fatigue += fatigue;
	CreateDamageToAiCharacter(&newMap[target.y][target.x].character, damage);
	AiCheckForHosting(&newMap[target.y][target.x].character, newMap);
	CheckDeadCharacter(&newMap[target.y][target.x].character, newMap);
	SetMoveToAction(target, newMap);
	DestroyMap(newMap);
}

void AiIterator::CheckForMove(SDL_Point pos)
{
	if (map[pos.y][pos.x].movable == TOOL_MAP_SIGN)
		return ;
	if (AtGoal(pos, character.position))
		return ;
	SDL_Point current = pos;
	SDL_Point goal = character.position;
	int damage = 0;
	int fatigue = 0;
	while (!AtGoal(current, goal))
	{
		SDL_Point next = GetNextPoint(current, map);
		damage += CheckMovePosition(next);
		fatigue += GetFatigueCost(next, current, map); //reverse order cause the iteration is in reverse...
		current = next;
	}
	HandleMoveAfterMath(pos, damage, fatigue);
}

void AiIterator::SetMoveToAction(SDL_Point pos, t_AiMapUnit **newMap)
{
	float score = SendToNextOne(newMap, character, 0);
	if (character.character->ally)
	{
		if (score > action.score)
		{
			action.ability = NULL;
			action.character = &character;
			action.pos = pos;
			action.same = false;
			action.score = score;
		}
		return ;
	}
	if (score < action.score)
	{
		action.ability = NULL;
		action.character = &character;
		action.pos = pos;
		action.same = false;
		action.score = score;
	}
}

static int GetFatigueCost(SDL_Point curr, SDL_Point next, t_AiMapUnit **map)
{
	int heightDiff = map[next.y][next.x].height - map[curr.y][curr.x].height;
	if (heightDiff < 0)
		return (1);
	int moveCost = 2 + heightDiff;
	float fatCost = (float)moveCost * 1.5f;
	return ((int)fatCost);
}

static SDL_Point GetNextPoint(SDL_Point curr, t_AiMapUnit **map)
{
	int score = map[curr.y][curr.x].movable;
	if (score == 0)
		return (curr);
	int left = AiGetXToLeft(curr);
	int right = AiGetXToRight(curr);
	SDL_Point save = curr;
	if (AiValidPos({left, curr.y - 1}))
	{
		if (map[curr.y - 1][left].movable < score)
		{
			score = map[curr.y - 1][left].movable;
			save = {left, curr.y - 1};
		}
	}
	if (AiValidPos({left, curr.y + 1}))
	{
		if (map[curr.y + 1][left].movable < score)
		{
			score = map[curr.y + 1][left].movable;
			save = {left, curr.y + 1};
		}
	}
	if (AiValidPos({right, curr.y - 1}))
	{
		if (map[curr.y - 1][right].movable < score)
		{
			score = map[curr.y - 1][right].movable;
			save = {right, curr.y - 1};
		}
	}
	if (AiValidPos({right, curr.y + 1}))
	{
		if (map[curr.y + 1][right].movable < score)
		{
			score = map[curr.y + 1][right].movable;
			save = {right, curr.y + 1};
		}
	}
	return (save);
}
