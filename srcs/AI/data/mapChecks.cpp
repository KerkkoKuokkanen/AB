
#include "../../../hdr/global.h"

static bool CheckCoordForBox(SDL_Point pos)
{
	if (!CheckIfValidPosition(pos))
		return (false);
	t_GMU *used = &gameState.battle.ground->map[pos.y][pos.x];
	if (used->additional.object == NULL)
		return (false);
	if (used->additional.type == AdditionalObjects::TOOLBOX)
		return (true);
	return (false);
}

bool CheckIfNextToToolBox(SDL_Point pos)
{
	int left = getXToLeft(pos);
	int right = getXToRight(pos);
	if (CheckCoordForBox({left, pos.y - 1}))
		return (true);
	if (CheckCoordForBox({left, pos.y + 1}))
		return (true);
	if (CheckCoordForBox({right, pos.y - 1}))
		return (true);
	if (CheckCoordForBox({right, pos.y + 1}))
		return (true);
	return (false);
}

void AiIterator::RoundStartMapChecks()
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (map[i][j].adds.smoke.isIt &&
				map[i][j].adds.smoke.parent == NULL)
			{
				map[i][j].adds.smoke.turns -= 1;
				if (map[i][j].adds.smoke.turns <= 0)
					map[i][j].adds.smoke.isIt = false;
			}
		}
	}
}

void AiIterator::TurnStartMapEffects()
{
	if (character->character->cSing != LION && character->character->cSing != THIEF)
		return ;
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (map[i][j].adds.phantom.parent == character->character)
			{
				map[i][j].adds.phantom.turns -= 1;
				if (map[i][j].adds.phantom.turns <= 0)
				{
					map[i][j].adds.phantom.isIt = false;
					map[i][j].adds.phantom.parent = NULL;
					map[i][j].adds.phantom.turns = 0;
				}
			}
			if (map[i][j].adds.smoke.parent == character->character)
			{
				map[i][j].adds.smoke.turns -= 1;
				if (map[i][j].adds.smoke.turns <= 0)
				{
					map[i][j].adds.smoke.isIt = false;
					map[i][j].adds.smoke.parent = NULL;
					map[i][j].adds.smoke.turns = 0;
				}
			}
		}
	}
}

static int GetCurrent(t_AiCharacter *curr)
{
	for (int i = 0; i < gameState.updateObjs.turnOrder->indicators.size(); i++)
	{
		Character *character = gameState.updateObjs.turnOrder->indicators[i].character;
		if (character == curr->character)
			return (i);
	}
	return (0);
}

static t_AiCharacter *GetFromMap(Character *character, t_AiMapUnit **map)
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (map[i][j].character == NULL)
				continue ;
			if (map[i][j].character->character == character)
			{
				if (map[i][j].character->alive)
					return (map[i][j].character);
			}
		}
	}
	return (NULL);
}

static t_AiCharacter *GetNext(int curr, t_AiMapUnit **map)
{
	t_AiCharacter *next = NULL;
	for (int i = curr + 1; i < gameState.updateObjs.turnOrder->indicators.size(); i++)
	{
		Character *character = gameState.updateObjs.turnOrder->indicators[i].character;
		next = GetFromMap(character, map);
		if (next != NULL)
			break ;
	}
	if (next != NULL)
		return (next);
	for (int i = 0; i < gameState.updateObjs.turnOrder->indicators.size(); i++)
	{
		Character *character = gameState.updateObjs.turnOrder->indicators[i].character;
		next = GetFromMap(character, map);
		if (next != NULL)
			return (next);
	}
	return (next);
}

t_SomeRetShit GetNextCharacter(t_AiCharacter *curr, t_AiCharacter *next, t_AiMapUnit **map)
{
	t_SomeRetShit ret = {NULL, 0};
	int current = GetCurrent(curr);
	next = GetNext(current, map);
	if (next == NULL)
	{
		ret = {next, 1};
		return (ret);
	}
	int nesta = GetCurrent(next);
	if (nesta <= current)
	{
		ret = {next, 2};
		return (ret);
	}
	ret = {next, 1};
	return (ret);
}

/* std::vector<Character*> GetPositionControllers(SDL_Point pos)
{
	int left = getXToLeft(pos);
	int right = getXToRight(pos);
} */
