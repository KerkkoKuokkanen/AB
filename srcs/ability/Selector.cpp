
#include "../../hdr/global.h"

void Selector::ClearPositionOutOfRange(int cleared, SDL_Point start)
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

Selector::Selector(SDL_Point start, int dist, int cleared, bool trees, GroundColoring *coloring)
{
	groundColoring = coloring;
	map = (int**)malloc(sizeof(int *) * gameState.battle.ground->map.size());
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
		map[i] = (int *)malloc(sizeof(int) * gameState.battle.ground->map[0].size());
	findMovables(map, dist, start);
	if (cleared > 0)
		ClearPositionOutOfRange(cleared, start);
	Color colorH(245, 147, 66);
	Color colorL(204, 126, 61);
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (map[i][j] != TOOL_MAP_SIGN)
			{
				SDL_Point pos = {j, i};
				groundColoring->SetColoredPosition(pos, colorH, colorL);
			}
		}
	}
	groundColoring->active = true;
}

Character *Selector::Update()
{
	Character *ret = NULL;
	Color purp = {255, 69, 56}, colorH(245, 147, 66), colorL(204, 126, 61);
	groundColoring->ClearMap();
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (map[i][j] == TOOL_MAP_SIGN)
				continue ;
			SDL_Point pos = {j, i};
			if (gameState.battle.ground->map[i][j].character != NULL
				&& (gameState.battle.ground->map[i][j].marked || gameState.battle.ground->map[i][j].character->hover)
				&& gameState.battle.ground->map[i][j].character->ally == false)
			{
				groundColoring->SetColoredPosition(pos, purp, purp);
				ret = gameState.battle.ground->map[i][j].character;
			}
			else
				groundColoring->SetColoredPosition(pos, colorH, colorL);
		}
	}
	return (ret);
}

void Selector::Destroy()
{
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
		free(map[i]);
	free(map);
	groundColoring->ClearMap();
	groundColoring->active = false;
}
