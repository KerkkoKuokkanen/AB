
#include "../../../hdr/global.h"

static Character *GetNextInTheList(Character *current)
{
	int index = (-1);
	for (int i = 0; i < gameState.updateObjs.turnOrder->indicators.size(); i++)
	{
		Character *charac = gameState.updateObjs.turnOrder->indicators[i].character;
		if (charac == current)
		{
			index = i;
			break ;
		}
	}
	if (index == (-1))
		return (current);
	if (index == gameState.updateObjs.turnOrder->indicators.size() - 1)
		return (gameState.updateObjs.turnOrder->indicators[0].character);
	return (gameState.updateObjs.turnOrder->indicators[index + 1].character);
}

static t_AiCharacter *FindInTheVector(std::vector<t_AiCharacter*> &charQ, Character *find)
{
	for (int i = 0; i < charQ.size(); i++)
	{
		if (charQ[i]->character == find)
			return (charQ[i]);
	}
	printf("error is here in the CrazyLoop with function FindInTheVector\n");
	return (NULL);
}

void OrderTheCharQ(std::vector<t_AiCharacter*> &charQ)
{
	Character *turn = NULL;
	int index = 0;
	for (int i = 0; i < gameState.updateObjs.turnOrder->indicators.size(); i++)
	{
		Character *charac = gameState.updateObjs.turnOrder->indicators[i].character;
		if (charac->turn)
		{
			index = i;
			turn = charac;
			break ;
		}
	}
	if (turn == NULL)
		return ;
	std::vector<t_AiCharacter*> newOrder = {};
	newOrder.push_back(FindInTheVector(charQ, turn));
	while (true)
	{
		Character *next = GetNextInTheList(newOrder[newOrder.size() - 1]->character);
		if (next == turn)
			break ;
		newOrder.push_back(FindInTheVector(charQ, next));
	}
	charQ.clear();
	charQ = newOrder;
}

static SDL_Point GetNextSmallest(SDL_Point pos, SDL_Point start)
{
	int distance = moveMaps.abilities[start.y][start.x].map[pos.y][pos.x];
	if (distance <= 0)
		return (pos);
	int left = AiGetXToLeft(pos);
	int right = AiGetXToRight(pos);
	SDL_Point positions[4] = {{left, pos.y - 1}, {left, pos.y + 1}, {right, pos.y - 1}, {right, pos.y + 1}};
	SDL_Point retPos = {-1, -1};
	for (int i = 0; i < 4; i++)
	{
		if (!AiValidPos(positions[i]))
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

int RangeBetweenPositions(t_AiMapUnit **map ,SDL_Point start, SDL_Point end)
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
