
#include "../../../hdr/global.h"

void AllSelector::ClearPositionOutOfRange(int cleared, SDL_Point start)
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

AllSelector::AllSelector(SDL_Point start, int dist, int cleared, GroundColoring *coloring, bool staticSearch, int statusSign)
{
	AllSelector::coloring = coloring;
	AllSelector::statusSign = statusSign;
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
			if (map[i][j] != TOOL_MAP_SIGN)
			{
				SDL_Point pos = {j, i};
				coloring->SetColoredPosition(pos, colorH, colorL);
			}
		}
	}
	coloring->active = true;
}

void AllSelector::UpdatePoints()
{
	Color purp = {84, 15, 20};
	Color colorH(245, 147, 66), colorL(204, 126, 61);
	coloring->ClearMap();
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (map[i][j] == TOOL_MAP_SIGN)
				continue ;
			SDL_Point pos = {j, i};
			Character *targ = gameState.battle.ground->map[i][j].character;
			if (targ != NULL && !targ->ally)
				coloring->SetColoredPosition(pos, purp, purp);
			else
				coloring->SetColoredPosition(pos, colorH, colorL);
		}
	}
}

void AllSelector::IncludePoint(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return ;
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return ;
	if (map == NULL)
		return ;
	map[pos.y][pos.x] = 1;
}

void AllSelector::Update()
{
	if (done)
		return ;
	UpdatePoints();
	if (gameState.keys.click == INITIAL_CLICK)
		done = true;
}

std::vector<SDL_Point> AllSelector::getTargets()
{
	std::vector<SDL_Point> ret;
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (map[i][j] == TOOL_MAP_SIGN)
				continue ;
			Character *targ = gameState.battle.ground->map[i][j].character;
			if (targ != NULL && !targ->ally)
				ret.push_back(targ->position);
		}
	}
	return (ret);
}

void AllSelector::Destroy()
{
	if (map != NULL)
	{
		for (int i = 0; i < gameState.battle.ground->map.size(); i++)
			free(map[i]);
		free(map);
	}
	coloring->ClearMap();
	coloring->active = false;
}
