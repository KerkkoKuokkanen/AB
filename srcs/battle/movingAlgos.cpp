
#include "../../hdr/global.h"

void BattleGround::ClearMovables()
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j].highlited)
				map[i][j].highlited = 0;
		}
	}
}

std::vector<SDL_Point> BattleGround::FindPath(SDL_Point cPos, SDL_Point tPos)
{
	SDL_Point currPos = tPos;
	std::vector<SDL_Point> ret;
	ret.push_back(tPos);
	int sizeModder = map[0].size() - 1;
	while (currPos.x != cPos.x || currPos.y != cPos.y)
	{
		int modder = (currPos.y % 2 == 0) ? (-1) : 1;
		int minMoves = toolMap[currPos.y][currPos.x];
		SDL_Point savedPos = {TOOL_MAP_SIGN, TOOL_MAP_SIGN};
		if (currPos.y > 0)
		{
			if (minMoves > toolMap[currPos.y - 1][currPos.x])
			{
				savedPos = {currPos.x, currPos.y - 1};
				minMoves = toolMap[currPos.y - 1][currPos.x];
			}
		}
		if (currPos.y < (map.size() - 1))
		{
			if (minMoves > toolMap[currPos.y + 1][currPos.x])
			{
				savedPos = {currPos.x, currPos.y + 1};
				minMoves = toolMap[currPos.y + 1][currPos.x];
			}
		}
		if (currPos.y > 0 && (currPos.x + modder) >= 0 && (currPos.x + modder) <= sizeModder)
		{
			if (minMoves > toolMap[currPos.y - 1][currPos.x + modder])
			{
				savedPos = {currPos.x + modder, currPos.y - 1};
				minMoves = toolMap[currPos.y - 1][currPos.x + modder];
			}
		}
		if (currPos.y < (map.size() - 1) && (currPos.x + modder) >= 0 && (currPos.x + modder) <= sizeModder)
		{
			if (minMoves > toolMap[currPos.y + 1][currPos.x + modder])
			{
				savedPos = {currPos.x + modder, currPos.y + 1};
				minMoves = toolMap[currPos.y + 1][currPos.x + modder];
			}
		}
		ret.push_back(savedPos);
		currPos = savedPos;
		if (minMoves == TOOL_MAP_SIGN)
			break ;
	}
	return (ret);
}

void BattleGround::SetMovables(Character *character)
{
	for (int i = 0; i < toolMap.size(); i++)
	{
		for (int j = 0; j < toolMap[i].size(); j++)
			toolMap[i][j] = TOOL_MAP_SIGN;
	}
	int highLightSign = (character->ally) ? 1 : 2;
	SDL_Point pos = character->getCoord();
	toolMap[pos.y][pos.x] = 0;
	map[pos.y][pos.x].highlited = highLightSign;
	int moves = (character->turn) ? character->moves : character->moves + 9;
	moves = (moves > 12) ? 12 : moves;
	int multi = (character->statuses.slowed == 1) ? 2 : 1;
	IterMapMovables(pos, 0, moves, highLightSign, multi);
}

void BattleGround::IterMapMovables(SDL_Point pos, int moves, int cMoves, int highLightSign, int multi)
{
	if (moves >= cMoves)
		return ;
	int currHeight = map[pos.y][pos.x].height;
	int modder = (pos.y % 2 == 0) ? (-1) : 1;
	int sizeModder = map[0].size() - 1;
	if (pos.y > 0 && map[pos.y - 1][pos.x].blocked == false)
	{
		int plus = 2 * multi;
		if (map[pos.y - 1][pos.x].height > currHeight)
			plus = (2 + (map[pos.y - 1][pos.x].height - currHeight)) * multi;
		else if (map[pos.y - 1][pos.x].height < currHeight)
			plus = 1 * multi;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y - 1][pos.x] > temp)
			{
				toolMap[pos.y - 1][pos.x] = temp;
				map[pos.y - 1][pos.x].highlited = highLightSign;
				SDL_Point location = {pos.x, pos.y - 1};
				IterMapMovables(location, temp, cMoves, highLightSign, multi);
			}
		}
	}
	if (pos.y < (map.size() - 1) && map[pos.y + 1][pos.x].blocked == false)
	{
		int plus = 2 * multi;
		if (map[pos.y + 1][pos.x].height > currHeight)
			plus = (2 + (map[pos.y + 1][pos.x].height - currHeight)) * multi;
		else if (map[pos.y + 1][pos.x].height < currHeight)
			plus = 1 * multi;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y + 1][pos.x] > temp)
			{
				toolMap[pos.y + 1][pos.x] = temp;
				map[pos.y + 1][pos.x].highlited = highLightSign;
				SDL_Point location = {pos.x, pos.y + 1};
				IterMapMovables(location, temp, cMoves, highLightSign, multi);
			}
		}
	}
	if (pos.y > 0 && (pos.x + modder) >= 0 && (pos.x + modder) <= sizeModder && map[pos.y - 1][pos.x + modder].blocked == false)
	{
		int plus = 2 * multi;
		if (map[pos.y - 1][pos.x + modder].height > currHeight)
			plus = (2 + (map[pos.y - 1][pos.x + modder].height - currHeight)) * multi;
		else if (map[pos.y - 1][pos.x + modder].height < currHeight)
			plus = 1 * multi;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y - 1][pos.x + modder] > temp)
			{
				toolMap[pos.y - 1][pos.x + modder] = temp;
				map[pos.y - 1][pos.x + modder].highlited = highLightSign;
				SDL_Point location = {pos.x + modder, pos.y - 1};
				IterMapMovables(location, temp, cMoves, highLightSign, multi);
			}
		}
	}
	if (pos.y < (map.size() - 1) && (pos.x + modder) >= 0 && (pos.x + modder) <= sizeModder && map[pos.y + 1][pos.x + modder].blocked == false)
	{
		int plus = 2 * multi;
		if (map[pos.y + 1][pos.x + modder].height > currHeight)
			plus = (2 + (map[pos.y + 1][pos.x + modder].height - currHeight)) * multi;
		else if (map[pos.y + 1][pos.x + modder].height < currHeight)
			plus = 1 * multi;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			if (toolMap[pos.y + 1][pos.x + modder] > temp)
			{
				toolMap[pos.y + 1][pos.x + modder] = temp;
				map[pos.y + 1][pos.x + modder].highlited = highLightSign;
				SDL_Point location = {pos.x + modder, pos.y + 1};
				IterMapMovables(location, temp, cMoves, highLightSign, multi);
			}
		}
	}
}
