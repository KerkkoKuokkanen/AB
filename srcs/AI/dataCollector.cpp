
#include "../../hdr/global.h"

void CreateTheMoveMaps()
{
	int height = gameState.battle.ground->map.size();
	int width = gameState.battle.ground->map[0].size();
	moveMaps.abilities = (t_MovementMap**)malloc(sizeof(t_MovementMap*) * height);
	moveMaps.staticMoves = (t_MovementMap**)malloc(sizeof(t_MovementMap*) * height);
	moveMaps.normalMoves = (t_MovementMap**)malloc(sizeof(t_MovementMap*) * height);
	for (int i = 0; i < height; i++)
	{
		moveMaps.abilities[i] = (t_MovementMap*)malloc(sizeof(t_MovementMap) * width);
		moveMaps.staticMoves[i] = (t_MovementMap*)malloc(sizeof(t_MovementMap) * width);
		moveMaps.normalMoves[i] = (t_MovementMap*)malloc(sizeof(t_MovementMap) * width);
		for (int j = 0; j < width; j++)
		{
			SDL_Point pos = {j, i};
			moveMaps.abilities[i][j].start = pos;
			moveMaps.staticMoves[i][j].start = pos;
			moveMaps.normalMoves[i][j].start = pos;
			moveMaps.abilities[i][j].map = (int**)malloc(sizeof(int*) * height);
			moveMaps.staticMoves[i][j].map = (int**)malloc(sizeof(int*) * height);
			moveMaps.normalMoves[i][j].map = (int**)malloc(sizeof(int*) * height);
			for (int k = 0; k < height; k++)
			{
				moveMaps.abilities[i][j].map[k] = (int*)malloc(sizeof(int) * width);
				moveMaps.staticMoves[i][j].map[k] = (int*)malloc(sizeof(int) * width);
				moveMaps.normalMoves[i][j].map[k] = (int*)malloc(sizeof(int) * width);
			}
			findMovables(moveMaps.abilities[i][j].map, 25, pos);
			findMovablesStatic(moveMaps.staticMoves[i][j].map, 25, pos);
			findMovablesNormal(moveMaps.normalMoves[i][j].map, 25, pos);
		}
	}
}

t_AiData CollectInitialData()
{
	t_AiData ret = {0};
	return ret;
}
