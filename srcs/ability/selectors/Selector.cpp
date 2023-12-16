
#include "../../../hdr/global.h"

static int **GetAdditionals(Character *mage)
{
	t_Ability *thisOne = NULL;
	for (int i = 0; i < mage->abilities.size(); i++)
	{
		if (mage->abilities[i].type == HOST_EYES)
		{
			thisOne = &mage->abilities[i];
			break ;
		}
	}
	t_HostEyes *used = (t_HostEyes*)thisOne->stats;
	int range = used->hostRange;
	int **map = (int**)malloc(sizeof(int *) * gameState.battle.ground->map.size());
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
		map[i] = (int *)malloc(sizeof(int) * gameState.battle.ground->map[0].size());
	Character *ret = (Character*)mage->statuses.hosting;
	findMovables(map, range, ret->position);
	return (map);
}

void ExtendSelector(Character *mage, Selector *selector)
{
	if (mage->statuses.hosting == NULL)
		return ;
	int **map = GetAdditionals(mage);
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (map[i][j] != TOOL_MAP_SIGN)
			{
				if (gameState.battle.ground->map[i][j].character != mage)
					selector->IncludePoint({j, i});
			}
		}
	}
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
		free(map[i]);
	free(map);
}

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

void Selector::IncludePoint(SDL_Point pos, int mark)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return ;
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return ;
	map[pos.y][pos.x] = mark;
}

void Selector::RemovePoint(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return ;
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return ;
	map[pos.y][pos.x] = TOOL_MAP_SIGN;
}

Selector::Selector(SDL_Point start, int dist, int cleared, GroundColoring *coloring, bool staticSearch)
{
	position = start;
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
			if (map[i][j] != TOOL_MAP_SIGN)
			{
				SDL_Point pos = {j, i};
				groundColoring->SetColoredPosition(pos, colorH, colorL);
			}
		}
	}
	groundColoring->active = true;
}

static bool CheckForAdditional(SDL_Point pos)
{
	t_Ability *abl = gameState.updateObjs.abilities->ability;
	t_GMU *point = &gameState.battle.ground->map[pos.y][pos.x];
	if (point->additional.object != NULL)
	{
		if (abl->targetAdds)
			return (true);
		return (false);
	}
	return (true);
}

Character *Selector::GetRet(Character *character, SDL_Point pos)
{
	if (character->killed)
		return (NULL);
	Color purp = {84, 15, 20}, colorH(245, 147, 66), colorL(204, 126, 61);
	Character *used = gameState.battle.ground->map[position.y][position.x].character;
	if (character->ally && sForAlly && used != character)
	{
		if (stunAlly)
		{
			if (character->statuses.stun == 0)
			{
				groundColoring->SetColoredPosition(pos, purp, purp);
				return (character);
			}
		}
		else
		{
			groundColoring->SetColoredPosition(pos, purp, purp);
			return (character);
		}
	}
	if (!character->ally && sForEnemy)
	{
		if (stunEnemy)
		{
			if (character->statuses.stun == 0)
			{
				groundColoring->SetColoredPosition(pos, purp, purp);
				return (character);
			}
		}
		else
		{
			groundColoring->SetColoredPosition(pos, purp, purp);
			return (character);
		}
	}
	groundColoring->SetColoredPosition(pos, colorH, colorL);
	return (NULL);
}

Character *Selector::Update()
{
	Character *ret = NULL;
	bool visited = false;
	Color colorH(245, 147, 66), colorL(204, 126, 61);
	groundColoring->ClearMap();
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (map[i][j] == TOOL_MAP_SIGN)
				continue ;
			SDL_Point pos = {j, i};
			if (gameState.battle.ground->map[i][j].character != NULL && CheckForAdditional(pos)
				&& (gameState.battle.ground->map[i][j].marked || gameState.battle.ground->map[i][j].character->hover))
			{
				if (additionalCompFunction != NULL)
				{
					if (additionalCompFunction(position, pos))
					{
						visited = true;
						ret = GetRet(gameState.battle.ground->map[i][j].character, pos);
					}
					else
						groundColoring->SetColoredPosition(pos, colorH, colorL);
				}
				else
				{
					visited = true;
					ret = GetRet(gameState.battle.ground->map[i][j].character, pos);
				}
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
