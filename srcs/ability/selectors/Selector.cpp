
#include "../../../hdr/global.h"

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

Selector::Selector(SDL_Point start, int dist, int cleared, GroundColoring *coloring, bool staticSearch, bool trees)
{
	Selector::trees = trees;
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

void Selector::SetBlockSprite(SDL_Point pos)
{
	if (!trees)
		return ;
	Character *character = NULL;
	Object *obj = NULL;
	if (gameState.battle.ground->map[pos.y][pos.x].obj != NULL)
		obj = gameState.battle.ground->map[pos.y][pos.x].obj;
	if (gameState.battle.ground->map[pos.y][pos.x].character != NULL)
		character = gameState.battle.ground->map[pos.y][pos.x].character;
	int size = 0;
	if (obj != NULL)
	{
		if (obj->size == 1)
			size = 1;
	}
	else
	{
		if (character == gameState.battle.ground->map[position.y][position.x].character)
		{
			if (block != NULL)
				delete block;
			block = NULL;
			return ;
		}
		size = 1;
	}
	Sprite *tile = gameState.battle.ground->GetSprite(pos);
	SDL_Rect dest = {tile->dest.x + 1340, tile->dest.y - 2300, 3150, 3150};
	if (block != NULL)
	{
		if (block->dest.x == dest.x && block->dest.y == dest.y)
			return ;
		delete block;
		block = NULL;
	}
	block = new Sprite(gameState.textures.blocks[size], dest, NULL, NULL, 0, FLIP_NONE);
	if (obj != NULL)
	{
		block->orderLayer = obj->sprite->orderLayer;
		block->z = obj->sprite->z + 0.1f;
	}
	else
	{
		block->orderLayer = character->sprite->orderLayer;
		block->z = character->sprite->z + 0.1f;
	}
	gameState.render->AddSprite(block, BATTLEGROUND_LAYER);
}

void Selector::SetBlock(SDL_Point target)
{
	int ret = CheckIfBlock(position, target);
	if (ret == 0)
	{
		if (block != NULL)
			delete block;
		block = NULL;
		return ;
	}
	SDL_Point pos = {0, 0};
	switch (ret)
	{
		case 1:
			pos = {getXToLeft(target), target.y - 1};
			break ;
		case 2:
			pos = {getXToLeft(target), target.y + 1};
			break ;
		case 3:
			pos = {getXToRight(target), target.y + 1};
			break ;
		case 4:
			pos = {getXToRight(target), target.y - 1};
			break ;
	}
	SetBlockSprite(pos);
}

Character *Selector::GetRet(Character *character, SDL_Point pos)
{
	Color purp = {84, 15, 20}, colorH(245, 147, 66), colorL(204, 126, 61);
	if (character->ally && sForAlly)
	{
		groundColoring->SetColoredPosition(pos, purp, purp);
		return (character);
	}
	if (!character->ally && sForEnemy)
	{
		SetBlock(pos);
		groundColoring->SetColoredPosition(pos, purp, purp);
		return (character);
	}
	groundColoring->SetColoredPosition(pos, colorH, colorL);
	return (NULL);
}

void Selector::BlockUpdater()
{
	if (block == NULL)
		return ;
	float fadeMulti = cos(gameState.updateObjs.fadeIter) / 2.0f + 0.5f;
	Uint8 add = (Uint8)(60.0f * fadeMulti);
	block->ColorMod(195 + add, 195 + add, 195 + add);
}

Character *Selector::Update()
{
	Character *ret = NULL;
	bool visited = false;
	Color purp = {84, 15, 20}, colorH(245, 147, 66), colorL(204, 126, 61);
	groundColoring->ClearMap();
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (map[i][j] == TOOL_MAP_SIGN)
				continue ;
			SDL_Point pos = {j, i};
			if (gameState.battle.ground->map[i][j].character != NULL
				&& (gameState.battle.ground->map[i][j].marked || gameState.battle.ground->map[i][j].character->hover))
			{
				visited = true;
				ret = GetRet(gameState.battle.ground->map[i][j].character, pos);
			}
			else
				groundColoring->SetColoredPosition(pos, colorH, colorL);
		}
	}
	if (visited)
		BlockUpdater();
	else
	{
		if (block != NULL)
			delete block;
		block = NULL;
	}
	return (ret);
}

void Selector::Destroy()
{
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
		free(map[i]);
	free(map);
	if (block != NULL)
		delete block;
	groundColoring->ClearMap();
	groundColoring->active = false;
}
