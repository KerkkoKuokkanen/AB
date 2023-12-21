
#include "../../hdr/ab.h"
#include "../../hdr/global.h"

void IterMapMovables(SDL_Point pos, int moves, int cMoves, int **toolMap);
void IterMapMovablesStatic(SDL_Point pos, int moves, int cMoves, int **toolMap);
void NormalIterMapMovables(SDL_Point pos, int moves, int cMoves, int **toolMap);

bool CheckIfValidPosition(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	return (true);
}

int GetFromPointX(SDL_Point position, SDL_Point nextPoint)
{
	int yAdder = 0;
	if (nextPoint.y > 0)
		yAdder = 1;
	if (nextPoint.y < 0)
		yAdder = (-1);
	if (nextPoint.x < 0)
	{
		SDL_Point temp = position;
		for (int i = 0; i < abs(nextPoint.x); i++)
		{
			temp.x = (nextPoint.y != 0) ? getXToLeft(temp) : temp.x - 1;
			temp.y += yAdder;
			if (nextPoint.y != 0)
				nextPoint.y -= yAdder;
		}
		return (temp.x);
	}
	if (nextPoint.x > 0)
	{
		SDL_Point temp = position;
		for (int i = 0; i < nextPoint.x; i++)
		{
			temp.x = (nextPoint.y != 0) ? getXToRight(temp) : temp.x + 1;
			temp.y += yAdder;
			if (nextPoint.y != 0)
				nextPoint.y -= yAdder;
		}
		return (temp.x);
	}
	return (position.x);
}

int GetFromPointY(SDL_Point position, SDL_Point nextPoint)
{
	return (position.y + nextPoint.y);
}

SDL_Point GetPositionFromCoordinates(SDL_Point position, SDL_Point nextPoint)
{
	int x = GetFromPointX(position, nextPoint);
	int y = GetFromPointY(position, nextPoint);
	SDL_Point ret = {x, y};
	return (ret);
}

SDL_Point GetValidPositionFromCoordinates(SDL_Point position, SDL_Point nextPoint)
{
	SDL_Point ret = GetPositionFromCoordinates(position, nextPoint);
	if (ret.x < 0 || ret.x >= gameState.battle.ground->map[0].size())
		return (position);
	if (ret.y < 0 || ret.y >= gameState.battle.ground->map.size())
		return (position);
	return (ret);
}

void findMovablesNormal(t_AiMapUnit **map, int moves, SDL_Point start)
{
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
			map[i][j].movable = TOOL_MAP_SIGN;
	}
	map[start.y][start.x].movable = 0;
	NormalIterMapMovables(start, 0, moves, map);
}

void findMovablesStatic(int **map, int moves, SDL_Point start)
{
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
			map[i][j] = TOOL_MAP_SIGN;
	}
	map[start.y][start.x] = 0;
	IterMapMovablesStatic(start, 0, moves, map);
}

void findMovables(int **map, int moves, SDL_Point start)
{
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
			map[i][j] = TOOL_MAP_SIGN;
	}
	map[start.y][start.x] = 0;
	IterMapMovables(start, 0, moves, map);
}

static bool AdditionalCheck(SDL_Point pos)
{
	if (gameState.battle.ground->map[pos.y][pos.x].obj != NULL)
	{
		if (gameState.battle.ground->map[pos.y][pos.x].obj->size == 1)
			return (true);
		if (gameState.battle.ground->map[pos.y][pos.x].blocked)
			return (false);
	}
	return (true);
}

static int AdditionalAdd(SDL_Point pos)
{
	if (gameState.battle.ground->map[pos.y][pos.x].obj != NULL)
		return (4);
	return (0);
}

void IterMapMovables(SDL_Point pos, int moves, int cMoves, int **toolMap)
{
	if (moves >= cMoves)
		return ;
	int currHeight = gameState.battle.ground->map[pos.y][pos.x].height;
	int modder = (pos.y % 2 == 0) ? (-1) : 1;
	int sizeModder = gameState.battle.ground->map[0].size() - 1;
	if (pos.y > 0 && AdditionalCheck(pos))
	{
		int plus = 2;
		if (gameState.battle.ground->map[pos.y - 1][pos.x].height > currHeight)
			plus = 2 + (gameState.battle.ground->map[pos.y - 1][pos.x].height - currHeight);
		else if (gameState.battle.ground->map[pos.y - 1][pos.x].height < currHeight)
			plus = 1;
		plus += AdditionalAdd({pos.x, pos.y - 1});
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y - 1][pos.x] > temp)
			{
				toolMap[pos.y - 1][pos.x] = temp;
				SDL_Point location = {pos.x, pos.y - 1};
				IterMapMovables(location, temp, cMoves, toolMap);
			}
		}
	}
	if (pos.y < (gameState.battle.ground->map.size() - 1) && AdditionalCheck(pos))
	{
		int plus = 2;
		if (gameState.battle.ground->map[pos.y + 1][pos.x].height > currHeight)
			plus = 2 + (gameState.battle.ground->map[pos.y + 1][pos.x].height - currHeight);
		else if (gameState.battle.ground->map[pos.y + 1][pos.x].height < currHeight)
			plus = 1;
		plus += AdditionalAdd({pos.x, pos.y + 1});
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y + 1][pos.x] > temp)
			{
				toolMap[pos.y + 1][pos.x] = temp;
				SDL_Point location = {pos.x, pos.y + 1};
				IterMapMovables(location, temp, cMoves, toolMap);
			}
		}
	}
	if (pos.y > 0 && (pos.x + modder) >= 0 && (pos.x + modder) <= sizeModder && AdditionalCheck(pos))
	{
		int plus = 2;
		if (gameState.battle.ground->map[pos.y - 1][pos.x + modder].height > currHeight)
			plus = 2 + (gameState.battle.ground->map[pos.y - 1][pos.x + modder].height - currHeight);
		else if (gameState.battle.ground->map[pos.y - 1][pos.x + modder].height < currHeight)
			plus = 1;
		plus += AdditionalAdd({pos.x + modder, pos.y - 1});
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y - 1][pos.x + modder] > temp)
			{
				toolMap[pos.y - 1][pos.x + modder] = temp;
				SDL_Point location = {pos.x + modder, pos.y - 1};
				IterMapMovables(location, temp, cMoves, toolMap);
			}
		}
	}
	if (pos.y < (gameState.battle.ground->map.size() - 1) && (pos.x + modder) >= 0 && (pos.x + modder) <= sizeModder && AdditionalCheck(pos))
	{
		int plus = 2;
		if (gameState.battle.ground->map[pos.y + 1][pos.x + modder].height > currHeight)
			plus = 2 + (gameState.battle.ground->map[pos.y + 1][pos.x + modder].height - currHeight);
		else if (gameState.battle.ground->map[pos.y + 1][pos.x + modder].height < currHeight)
			plus = 1;
		plus += AdditionalAdd({pos.x + modder, pos.y + 1});
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y + 1][pos.x + modder] > temp)
			{
				toolMap[pos.y + 1][pos.x + modder] = temp;
				SDL_Point location = {pos.x + modder, pos.y + 1};
				IterMapMovables(location, temp, cMoves, toolMap);
			}
		}
	}
}

void IterMapMovablesStatic(SDL_Point pos, int moves, int cMoves, int **toolMap)
{
	if (moves >= cMoves)
		return ;
	int modder = (pos.y % 2 == 0) ? (-1) : 1;
	int sizeModder = gameState.battle.ground->map[0].size() - 1;
	if (pos.y > 0 && AdditionalCheck(pos))
	{
		int plus = 2;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y - 1][pos.x] > temp)
			{
				toolMap[pos.y - 1][pos.x] = temp;
				SDL_Point location = {pos.x, pos.y - 1};
				IterMapMovablesStatic(location, temp, cMoves, toolMap);
			}
		}
	}
	if (pos.y < (gameState.battle.ground->map.size() - 1) && AdditionalCheck(pos))
	{
		int plus = 2;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y + 1][pos.x] > temp)
			{
				toolMap[pos.y + 1][pos.x] = temp;
				SDL_Point location = {pos.x, pos.y + 1};
				IterMapMovablesStatic(location, temp, cMoves, toolMap);
			}
		}
	}
	if (pos.y > 0 && (pos.x + modder) >= 0 && (pos.x + modder) <= sizeModder && AdditionalCheck(pos))
	{
		int plus = 2;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y - 1][pos.x + modder] > temp)
			{
				toolMap[pos.y - 1][pos.x + modder] = temp;
				SDL_Point location = {pos.x + modder, pos.y - 1};
				IterMapMovablesStatic(location, temp, cMoves, toolMap);
			}
		}
	}
	if (pos.y < (gameState.battle.ground->map.size() - 1) && (pos.x + modder) >= 0 && (pos.x + modder) <= sizeModder && AdditionalCheck(pos))
	{
		int plus = 2;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y + 1][pos.x + modder] > temp)
			{
				toolMap[pos.y + 1][pos.x + modder] = temp;
				SDL_Point location = {pos.x + modder, pos.y + 1};
				IterMapMovablesStatic(location, temp, cMoves, toolMap);
			}
		}
	}
}

void NormalIterMapMovables(SDL_Point pos, int moves, int cMoves, t_AiMapUnit **toolMap)
{
	if (moves >= cMoves)
		return ;
	int currHeight = gameState.battle.ground->map[pos.y][pos.x].height;
	int modder = (pos.y % 2 == 0) ? (-1) : 1;
	int sizeModder = gameState.battle.ground->map[0].size() - 1;
	if (pos.y > 0 && gameState.battle.ground->map[pos.y - 1][pos.x].blocked == false)
	{
		int plus = 2;
		if (gameState.battle.ground->map[pos.y - 1][pos.x].height > currHeight)
			plus = (2 + (gameState.battle.ground->map[pos.y - 1][pos.x].height - currHeight));
		else if (gameState.battle.ground->map[pos.y - 1][pos.x].height < currHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y - 1][pos.x].movable > temp)
			{
				toolMap[pos.y - 1][pos.x].movable = temp;
				SDL_Point location = {pos.x, pos.y - 1};
				NormalIterMapMovables(location, temp, cMoves, toolMap);
			}
		}
	}
	if (pos.y < (gameState.battle.ground->map.size() - 1) && gameState.battle.ground->map[pos.y + 1][pos.x].blocked == false)
	{
		int plus = 2;
		if (gameState.battle.ground->map[pos.y + 1][pos.x].height > currHeight)
			plus = (2 + (gameState.battle.ground->map[pos.y + 1][pos.x].height - currHeight));
		else if (gameState.battle.ground->map[pos.y + 1][pos.x].height < currHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y + 1][pos.x].movable > temp)
			{
				toolMap[pos.y + 1][pos.x].movable = temp;
				SDL_Point location = {pos.x, pos.y + 1};
				NormalIterMapMovables(location, temp, cMoves, toolMap);
			}
		}
	}
	if (pos.y > 0 && (pos.x + modder) >= 0 && (pos.x + modder) <= sizeModder && gameState.battle.ground->map[pos.y - 1][pos.x + modder].blocked == false)
	{
		int plus = 2;
		if (gameState.battle.ground->map[pos.y - 1][pos.x + modder].height > currHeight)
			plus = (2 + (gameState.battle.ground->map[pos.y - 1][pos.x + modder].height - currHeight));
		else if (gameState.battle.ground->map[pos.y - 1][pos.x + modder].height < currHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y - 1][pos.x + modder].movable > temp)
			{
				toolMap[pos.y - 1][pos.x + modder].movable = temp;
				SDL_Point location = {pos.x + modder, pos.y - 1};
				NormalIterMapMovables(location, temp, cMoves, toolMap);
			}
		}
	}
	if (pos.y < (gameState.battle.ground->map.size() - 1) && (pos.x + modder) >= 0 && (pos.x + modder) <= sizeModder && gameState.battle.ground->map[pos.y + 1][pos.x + modder].blocked == false)
	{
		int plus = 2;
		if (gameState.battle.ground->map[pos.y + 1][pos.x + modder].height > currHeight)
			plus = (2 + (gameState.battle.ground->map[pos.y + 1][pos.x + modder].height - currHeight));
		else if (gameState.battle.ground->map[pos.y + 1][pos.x + modder].height < currHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y + 1][pos.x + modder].movable > temp)
			{
				toolMap[pos.y + 1][pos.x + modder].movable = temp;
				SDL_Point location = {pos.x + modder, pos.y + 1};
				NormalIterMapMovables(location, temp, cMoves, toolMap);
			}
		}
	}
}
