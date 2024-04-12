
#include "../../../hdr/global.h"
#define BIG_NUMBER 999999

static int AAiGetXToRight(SDL_Point pos)
{
	int modder = (pos.y % 2 == 0) ? 0 : 1;
	return (pos.x + modder);
}

static int AAiGetXToLeft(SDL_Point pos)
{
	int modder = (pos.y % 2 == 0) ? -1 : 0;
	return (pos.x + modder);
}

static bool AAiValidPos(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	return (true);
}

static SDL_Point GetNextSmallest(SDL_Point pos, SDL_Point start)
{
	int distance = moveMaps.abilities[start.y][start.x].map[pos.y][pos.x];
	if (distance <= 0)
		return (pos);
	int left = AAiGetXToLeft(pos);
	int right = AAiGetXToRight(pos);
	SDL_Point positions[4] = {{left, pos.y - 1}, {left, pos.y + 1}, {right, pos.y - 1}, {right, pos.y + 1}};
	SDL_Point retPos = {-1, -1};
	for (int i = 0; i < 4; i++)
	{
		if (!AAiValidPos(positions[i]))
			continue ;
		int found = moveMaps.abilities[start.y][start.x].map[positions[i].y][positions[i].x];
		if (found == TOOL_MAP_SIGN)
			continue ;
		if (found < distance)
		{
			distance = found;
			retPos = {positions[i].x, positions[i].y};
		}
	}
	return (retPos);
}

static int RangeBetweenPositionsLocal(t_AiMapUnit **map ,SDL_Point start, SDL_Point end)
{
	int distance = moveMaps.abilities[start.y][start.x].map[end.y][end.x];
	int current = distance;
	SDL_Point next = end;
	while (current != 0)
	{
		next = GetNextSmallest(next, start);
		if (next.x == (-1))
			return (-1);
		current = moveMaps.abilities[start.y][start.x].map[next.y][next.x];
		if (map[next.y][next.x].blocked)
			distance += 4;
	}
	return (distance);
}

static int GetCharactersDistToPosition(t_AiMapUnit **map, SDL_Point position, t_AiCharacter *character)
{
	SDL_Point start = character->position;
	int dist = RangeBetweenPositionsLocal(map, start, position);
	return (dist);
}

static int CharacterDistanceToPosition(SDL_Point pos, t_AiCharacter *target, bool staticSearch)
{
	SDL_Point targ = target->position;
	if (staticSearch)
	{
		int dist = moveMaps.staticMoves[targ.y][targ.x].map[pos.y][pos.x];
		return (dist);
	}
	int dist = moveMaps.abilities[targ.y][targ.x].map[pos.y][pos.x];
	return (dist);
}

static int PositionHasTargetsInRange(int range, SDL_Point position, t_AiCharacter *character, std::vector<t_AiCharacter*> &charQ, int targetType, bool staticDist, bool ally)
{
	int closest = BIG_NUMBER;
	for (int i = 0; i < charQ.size(); i++)
	{
		if (targetType == 0 && charQ[i]->character->ally == ally)
			continue ;
		if (targetType == 1 && charQ[i]->character->ally != ally)
			continue ;
		if (charQ[i] == character)
			continue ;
		SDL_Point check = charQ[i]->position;
		int dist = CharacterDistanceToPosition(check, charQ[i], staticDist);
		if (dist == 0)
			continue ;
		if (dist < closest)
			closest = dist;
	}
	if (closest == BIG_NUMBER)
		return (-1);
	return (closest);
}

t_PointDist ReturnMapPositionDistances(SDL_Point check, t_AiMapUnit **map, t_AiCharacter *character, int distance, bool staticDist, int targetType, int saveCount, std::vector<t_AiCharacter*> &charQ)
{
	t_PointDist ret = {check, -1, -1};
	int dist = PositionHasTargetsInRange(distance, check, character, charQ, targetType, staticDist, character->character->ally);
	if (dist == (-1))
		return (ret);
	ret.distance = GetCharactersDistToPosition(map, check, character);
	ret.closest = dist;
	return (ret);
}
