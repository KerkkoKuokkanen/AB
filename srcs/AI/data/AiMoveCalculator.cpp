
#include "../../../hdr/global.h"
static SDL_Point GetNextPoint(SDL_Point curr, t_AiMapUnit **map);

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
	if (pos.x < 0 || pos.x > gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y > gameState.battle.ground->map.size())
		return (false);
	return (true);
}

/* static bool CheckForAdditionalValid(Character *target, SDL_Point pos)
{
	t_GMU *used = &gameState.battle.ground->map[pos.y][pos.x];
	if (used->additional.object == NULL)
		return (false);
	if (used->additional.type != AdditionalObjects::PHANTOM_KNIGHT)
		return (false);
	PhantomKnight *ret = (PhantomKnight*)used->additional.object;
	Character *PC = ret->character;
	if (PC->ally == target->ally)
		return (false);
	return (true);
} */

static bool AdditionalValidation(SDL_Point pos, t_AiMapUnit **map, bool ally)
{
	if (map[pos.y][pos.x].adds.phantom == false)
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

		}
	}
}

int AiIterator::CheckMovePosition(SDL_Point pos)
{
	std::vector<SDL_Point> damagers;
	GetAiOppDamagers(damagers, map, pos, character.character->ally);
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
	while (!AtGoal(current, goal))
	{
		SDL_Point next = GetNextPoint(current, map);
		CheckMovePosition(next);
		current = next;
	}
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
