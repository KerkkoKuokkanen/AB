
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

t_AiData *GetTheAiDataStruct()
{
	t_AiData *ret = (t_AiData*)malloc(sizeof(t_AiData));
	bzero(ret, sizeof(t_AiData));
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	ret->map = (t_AiMapUnit**)malloc(sizeof(t_AiMapUnit*) * h);
	bzero(ret->map,	sizeof(t_AiMapUnit*) * h);
	for (int i = 0; i < h; i++)
	{
		ret->map[i] = (t_AiMapUnit*)malloc(sizeof(t_AiMapUnit) * w);
		bzero(ret->map[i], sizeof(t_AiMapUnit) * w);
	}
	return (ret);
	
}

void FreeTheAiDataStruct(t_AiData *data)
{
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
		free(data->map[i]);
	free(data->map);
	free(data);
}

static Character *SetAiDataCharacterOrder(t_AiData *data)
{
	Character *ret = NULL;
	for (int i = 0; i < gameState.updateObjs.turnOrder->indicators.size(); i++)
	{
		Character *add = gameState.updateObjs.turnOrder->indicators[i].character;
		t_AiCharacter addToTurnQ;
		addToTurnQ.character = add;
		addToTurnQ.health = add->stats.health;
		addToTurnQ.armor = add->stats.armor;
		addToTurnQ.alive = !add->killed;
		data->turnQueue.push_back(addToTurnQ);
		if (add->turn)
			ret = add;
	}
	return ret;
}

static void SetPositionCharacter(t_AiMapUnit *used, SDL_Point pos)
{
	t_GMU *check = &gameState.battle.ground->map[pos.y][pos.x];
	if (check->character == NULL)
	{
		used->character.alive = false;
		used->character.armor = 0;
		used->character.health = 0;
		used->character.character = NULL;
		return ;
	}
	used->character.alive = !check->character->killed;
	used->character.armor = check->character->stats.armor;
	used->character.health = check->character->stats.health;
	used->character.character = check->character;
}

static void SetAiDataMap(t_AiData *data)
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			t_GMU *point = &gameState.battle.ground->map[i][j];
			data->map[i][j].blocked = point->blocked;
			data->map[i][j].height = point->height;
			data->map[i][j].generals.obj = point->obj;
			data->map[i][j].generals.add = point->additional;
			data->map[i][j].specials.smoked = CheckIfSmoked({j, i});
			data->map[i][j].specials.toolBoxAbilities = CheckIfNextToToolBox({j, i});
			SetPositionCharacter(&data->map[i][j], {j, i});
		}
	}
}

t_AiData *CollectInitialData()
{
	t_AiData *ret = GetTheAiDataStruct();
	Character *curr = SetAiDataCharacterOrder(ret);
	ret->current = {curr, curr->stats.health, curr->stats.armor, !curr->killed};
	return (ret);
}
