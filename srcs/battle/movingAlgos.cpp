
#include "../../hdr/global.h"

void BattleGround::ClearMovables()
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j].highlited)
				map[i][j].highlited = false;
		}
	}
}

void BattleGround::SetMovables(Character *character)
{
	for (int i = 0; i < toolMap.size(); i++)
	{
		for (int j = 0; j < toolMap[i].size(); j++)
			toolMap[i][j] = TOOL_MAP_SIGN;
	}
	SDL_Point pos = character->getCoord();
	map[pos.y][pos.x].highlited = true;
	IterMapMovables(pos, 0, character->moves);
}

void BattleGround::IterMapMovables(SDL_Point pos, int moves, int cMoves)
{
	if (moves >= cMoves)
		return ;
	int currHeight = map[pos.y][pos.x].height;
	int modder = (pos.y % 2 == 0) ? (-1) : 1;
	int sizeModder = map[0].size() - 1;
	if (pos.y > 0 && map[pos.y - 1][pos.x].blocked == false)
	{
		int plus = 2;
		if (map[pos.y - 1][pos.x].height > currHeight)
			plus = 2 + (map[pos.y - 1][pos.x].height - currHeight);
		else if (map[pos.y - 1][pos.x].height < currHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y - 1][pos.x] > temp)
			{
				toolMap[pos.y - 1][pos.x] = temp;
				map[pos.y - 1][pos.x].highlited = true;
				SDL_Point location = {pos.x, pos.y - 1};
				IterMapMovables(location, temp, cMoves);
			}
		}
	}
	if (pos.y < (map.size() - 1) && map[pos.y + 1][pos.x].blocked == false)
	{
		int plus = 2;
		if (map[pos.y + 1][pos.x].height > currHeight)
			plus = 2 + (map[pos.y + 1][pos.x].height - currHeight);
		else if (map[pos.y + 1][pos.x].height < currHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y + 1][pos.x] > temp)
			{
				toolMap[pos.y + 1][pos.x] = temp;
				map[pos.y + 1][pos.x].highlited = true;
				SDL_Point location = {pos.x, pos.y + 1};
				IterMapMovables(location, temp, cMoves);
			}
		}
	}
	if (pos.y > 0 && pos.x > 0 && pos.x < sizeModder && map[pos.y - 1][pos.x + modder].blocked == false)
	{
		int plus = 2;
		if (map[pos.y - 1][pos.x + modder].height > currHeight)
			plus = 2 + (map[pos.y - 1][pos.x + modder].height - currHeight);
		else if (map[pos.y - 1][pos.x + modder].height < currHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y - 1][pos.x + modder] > temp)
			{
				toolMap[pos.y - 1][pos.x + modder] = temp;
				map[pos.y - 1][pos.x + modder].highlited = true;
				SDL_Point location = {pos.x + modder, pos.y - 1};
				IterMapMovables(location, temp, cMoves);
			}
		}
	}
	if (pos.y < (map.size() - 1) && pos.x > 0 && pos.x < sizeModder && map[pos.y + 1][pos.x + modder].blocked == false)
	{
		int plus = 2;
		if (map[pos.y + 1][pos.x + modder].height > currHeight)
			plus = 2 + (map[pos.y + 1][pos.x + modder].height - currHeight);
		else if (map[pos.y + 1][pos.x + modder].height < currHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y + 1][pos.x + modder] > temp)
			{
				toolMap[pos.y + 1][pos.x + modder] = temp;
				map[pos.y + 1][pos.x + modder].highlited = true;
				SDL_Point location = {pos.x + modder, pos.y + 1};
				IterMapMovables(location, temp, cMoves);
			}
		}
	}
}
