
#include "../../../hdr/global.h"

void CreateTheMoveMaps()
{
	int height = gameState.battle.ground->map.size();
	int width = gameState.battle.ground->map[0].size();
	moveMaps.abilities = (t_MovementMap**)malloc(sizeof(t_MovementMap*) * height);
	moveMaps.staticMoves = (t_MovementMap**)malloc(sizeof(t_MovementMap*) * height);
	for (int i = 0; i < height; i++)
	{
		moveMaps.abilities[i] = (t_MovementMap*)malloc(sizeof(t_MovementMap) * width);
		moveMaps.staticMoves[i] = (t_MovementMap*)malloc(sizeof(t_MovementMap) * width);
		for (int j = 0; j < width; j++)
		{
			SDL_Point pos = {j, i};
			moveMaps.abilities[i][j].start = pos;
			moveMaps.staticMoves[i][j].start = pos;
			moveMaps.abilities[i][j].map = (int**)malloc(sizeof(int*) * height);
			moveMaps.staticMoves[i][j].map = (int**)malloc(sizeof(int*) * height);
			for (int k = 0; k < height; k++)
			{
				moveMaps.abilities[i][j].map[k] = (int*)malloc(sizeof(int) * width);
				moveMaps.staticMoves[i][j].map[k] = (int*)malloc(sizeof(int) * width);
			}
			findMovables(moveMaps.abilities[i][j].map, 25, pos);
			findMovablesStatic(moveMaps.staticMoves[i][j].map, 25, pos);
		}
	}
}

static t_AiCharacter SetTheCharacter(Character *character)
{
	t_AiCharacter ret;
	if (character == NULL)
	{
		ret.alive = false;
		ret.armor = 0;
		ret.health = 0;
		ret.fatigue = 0;
		ret.moves = 0;
		ret.position = {0, 0};
		ret.character = NULL;
		return (ret);
	}
	ret.alive = !character->killed;
	ret.armor = character->stats.armor;
	ret.health = character->stats.health;
	ret.fatigue = character->stats.fatigue;
	ret.moves = character->moves;
	ret.character = character;
	ret.position = character->position;
	return (ret);
}

static t_AiMapObj SetTheObj(Object *obj)
{
	t_AiMapObj ret;
	if (obj == NULL)
	{
		ret.obj = false;
		ret.size = 0;
		return (ret);
	}
	ret.obj = true;
	ret.size = obj->size;
	return (ret);
}

t_AiCharacter GetTheStartingTurnForAi()
{
	Character *used = NULL;
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		if (gameState.battle.ground->characters[i].character->turn)
			used = gameState.battle.ground->characters[i].character;
	}
	return (SetTheCharacter(used));
}

static int **GetMoveMap()
{
	int w = gameState.battle.ground->map[0].size();
	int h = gameState.battle.ground->map.size();
	int **ret = (int**)malloc(sizeof(int*) * h);
	for (int i = 0; i < h; i++)
		ret[i] = (int*)malloc(sizeof(int) * w);
	return (ret);
}

void FreeMoveMap(int **map)
{
	int h = gameState.battle.ground->map.size();
	for (int i = 0; i < h; i++)
		free(map[i]);
	free(map);
}

void GetAiMapMoves(t_AiCharacter *aiChar, t_AiMapUnit **map)
{
	SDL_Point pos = aiChar->position;
	int moves = aiChar->moves;
	findMovablesNormal(map, moves, pos);
}

void SetAiMapAdds(t_AiMapUnit &unit, SDL_Point pos)
{
	t_GMU *point = &gameState.battle.ground->map[pos.y][pos.x];
	unit.adds.smoke = CheckIfSmoked(pos);
	unit.adds.phantom = (point->additional.type == AdditionalObjects::PHANTOM_KNIGHT) ? true : false;
	unit.adds.toolBox = (point->additional.type == AdditionalObjects::TOOLBOX) ? true : false;
}

void SetAiDataMapInitial(t_AiMapUnit **map)
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			t_GMU *point = &gameState.battle.ground->map[i][j];
			map[i][j].blocked = point->blocked;
			map[i][j].height = point->height;
			map[i][j].character = SetTheCharacter(point->character);
			map[i][j].obj = SetTheObj(point->obj);
			SetAiMapAdds(map[i][j], {j, i});
			map[i][j].movable = TOOL_MAP_SIGN;
		}
	}
}

static bool IsCharacter(t_AiMapUnit &point)
{
	if (point.character.character == NULL)
		return (false);
	return (true);
}

void DestroyMap(t_AiMapUnit **map)
{
	int h = gameState.battle.ground->map.size();
	for (int i = 0; i < h; i++)
		free(map[i]);
	free(map);
}

t_AiMapUnit **GetTheMap()
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	t_AiMapUnit **map = (t_AiMapUnit**)malloc(sizeof(t_AiMapUnit*) * h);
	for (int i = 0; i < h; i++)
		map[i] = (t_AiMapUnit*)malloc(sizeof(t_AiMapUnit) * w);
	SetAiDataMapInitial(map);
	return (map);
}

float GetAiScore(t_AiMapUnit **map, bool ally)
{
	float ah = 0.0f;
	float eh = 0.0f;
	float fat = 0.0f;
	int w = gameState.battle.ground->map[0].size();
	int h = gameState.battle.ground->map.size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			bool value = IsCharacter(map[i][j]);
			if (value == false)
				continue ;
			if (map[i][j].character.character->ally == ally)
			{
				ah += (float)(map[i][j].character.health + map[i][j].character.armor);
				fat += (float)map[i][j].character.fatigue;
			}
			else
				eh += (float)(map[i][j].character.health + map[i][j].character.armor);
		}
	}
	if (fat < 36.0f)
		fat = 0.0f;
	float finalValue = ah - eh - fat;
	return (finalValue);
}
