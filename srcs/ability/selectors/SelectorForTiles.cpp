
#include "../../../hdr/global.h"

void TileSelector::ClearPositionOutOfRange(int cleared, SDL_Point start)
{
	int **temp = (int**)malloc(sizeof(int *) * gameState.battle.ground->map.size());
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
		temp[i] = (int *)malloc(sizeof(int) * gameState.battle.ground->map[0].size());
	findMovablesStatic(temp, cleared, start);
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (temp[i][j] != TOOL_MAP_SIGN)
				map[i][j] = TOOL_MAP_SIGN;
		}
	}
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
		free(temp[i]);
	free(temp);
}

void TileSelector::IncludePoint(SDL_Point pos, int mark)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return ;
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return ;
	map[pos.y][pos.x] = mark;
}

TileSelector::TileSelector(SDL_Point start, int dist, int cleared, GroundColoring *coloring, bool blockers, bool staticSearch)
{
	groundColoring = coloring;
	map = (int**)malloc(sizeof(int *) * gameState.battle.ground->map.size());
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
		map[i] = (int *)malloc(sizeof(int) * gameState.battle.ground->map[0].size());
	if (dist > 0)
	{
		if (staticSearch)
			findMovablesStatic(map, dist, start);
		else
			findMovables(map, dist, start);
	}
	if (cleared > 0)
		ClearPositionOutOfRange(cleared, start);
	Color colorH(245, 147, 66);
	Color colorL(204, 126, 61);
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (blockers && map[i][j] != TOOL_MAP_SIGN && gameState.battle.ground->map[i][j].blocked)
				map[i][j] = TOOL_MAP_SIGN;
			if (map[i][j] != TOOL_MAP_SIGN)
			{
				SDL_Point pos = {j, i};
				groundColoring->SetColoredPosition(pos, colorH, colorL);
			}
		}
	}
	groundColoring->active = true;
}

SDL_Point TileSelector::Update()
{
	SDL_Point ret = {-1, -1};
	Color purp = {84, 15, 20}, colorH(245, 147, 66), colorL(204, 126, 61);
	groundColoring->ClearMap();
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (map[i][j] == TOOL_MAP_SIGN)
				continue ;
			SDL_Point pos = {j, i};
			if (gameState.battle.ground->map[i][j].marked ||
				(gameState.battle.ground->map[i][j].character != NULL && gameState.battle.ground->map[i][j].character->hover))
			{
				ret = pos;
				groundColoring->SetColoredPosition(pos, purp, purp);
			}
			else
				groundColoring->SetColoredPosition(pos, colorH, colorL);
		}
	}
	return (ret);
}

void TileSelector::Destroy()
{
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
		free(map[i]);
	free(map);
	groundColoring->ClearMap();
	groundColoring->active = false;
}
