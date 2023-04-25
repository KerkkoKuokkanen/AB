
#include "../../hdr/global.h"

void BattleGround::MovingUpdate()
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j].highlited)
			{
				int index = i * map[0].size() + j;
				sprites[index][sprites[index].size() - 1].ColorMod(107, 255, 122);
			}
		}
	}
}

void BattleGround::ClearMovables()
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			int index = i * map[0].size() + j;
			if (map[i][j].highlited)
			{
				map[i][j].highlited = false;
				sprites[index][sprites[index].size() - 1].ClearColorMod();
			}
		}
	}
}

void BattleGround::SetMovables(Character *character)
{
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
	if (pos.y > 0)
	{
		int plus = 2;
		if (map[pos.y - 1][pos.x].height > currHeight)
			plus = 2 + (map[pos.y - 1][pos.x].height - currHeight);
		else if (map[pos.y - 1][pos.x].height < currHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			map[pos.y - 1][pos.x].highlited = true;
			SDL_Point location = {pos.x, pos.y - 1};
			IterMapMovables(location, temp, cMoves);
		}
	}
	if (pos.y < (map.size() - 1))
	{
		int plus = 2;
		if (map[pos.y + 1][pos.x].height > currHeight)
			plus = 2 + (map[pos.y + 1][pos.x].height - currHeight);
		else if (map[pos.y + 1][pos.x].height < currHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			map[pos.y + 1][pos.x].highlited = true;
			SDL_Point location = {pos.x, pos.y + 1};
			IterMapMovables(location, temp, cMoves);
		}
	}
	if (pos.y > 0 && pos.x > 0 && pos.x < sizeModder)
	{
		int plus = 2;
		if (map[pos.y - 1][pos.x + modder].height > currHeight)
			plus = 2 + (map[pos.y - 1][pos.x + modder].height - currHeight);
		else if (map[pos.y - 1][pos.x + modder].height < currHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			map[pos.y - 1][pos.x + modder].highlited = true;
			SDL_Point location = {pos.x + modder, pos.y - 1};
			IterMapMovables(location, temp, cMoves);
		}
	}
	if (pos.y < (map.size() - 1) && pos.x > 0 && pos.x < sizeModder)
	{
		int plus = 2;
		if (map[pos.y + 1][pos.x + modder].height > currHeight)
			plus = 2 + (map[pos.y + 1][pos.x + modder].height - currHeight);
		else if (map[pos.y + 1][pos.x + modder].height < currHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			map[pos.y + 1][pos.x + modder].highlited = true;
			SDL_Point location = {pos.x + modder, pos.y + 1};
			IterMapMovables(location, temp, cMoves);
		}
	}
}
