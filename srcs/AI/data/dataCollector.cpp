
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
	ret.alive = !character->killed;
	ret.armor = character->stats.armor;
	ret.health = character->stats.health;
	ret.fatigue = character->stats.fatigue;
	ret.moves = character->moves;
	ret.character = character;
	ret.position = character->position;
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

int **GetMoves(t_AiCharacter *aiChar)
{
	SDL_Point pos = aiChar->position;
	int moves = aiChar->moves;
	int **map = GetMoveMap();
	findMovablesNormal(map, moves, pos);
	return (map);
}
