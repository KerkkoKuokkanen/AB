
#include "../../../hdr/global.h"

uint8_t gameWidth = 0;
uint8_t gameHeight = 0;

void InitAiIteration()
{
	int w = gameState.battle.ground->map[0].size();
	int h = gameState.battle.ground->map.size();
	gameWidth = (uint8_t)w;
	gameHeight = (uint8_t)h;
	InitCrazyLoopForIteration();
}

static int Ai2GetXToRight(SDL_Point pos)
{
	int modder = (pos.y % 2 == 0) ? 0 : 1;
	return (pos.x + modder);
}

static int Ai2GetXToLeft(SDL_Point pos)
{
	int modder = (pos.y % 2 == 0) ? -1 : 0;
	return (pos.x + modder);
}

static bool Ai2ValidPos(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	return (true);
}

uint16_t **CreateMoveMapForAi2()
{
	uint16_t **map;
	map = (uint16_t**)malloc(sizeof(uint16_t*) * gameHeight);
	for (uint8_t i = 0; i < gameHeight; i++)
	{
		map[i] = (uint16_t*)malloc(sizeof(uint16_t) * gameWidth);
		bzero(map[i], sizeof(uint16_t) * gameWidth);
	}
	return (map);
}

void DestroyMoveMap2(uint16_t **map)
{
	for (uint8_t i = 0; i < gameHeight; i++)
		free(map[i]);
	free(map);
}

static void Ai2IterMoveMap(uint16_t **moveMap, int moves, int targetMoves, SDL_Point pos)
{
	int left = Ai2GetXToLeft(pos);
	int right = Ai2GetXToRight(pos);
	int currentHeight = gameState.battle.ground->map[pos.y][pos.x].height;
	SDL_Point positions[4] = {{left, pos.y + 1}, {left, pos.y - 1}, {right, pos.y + 1}, {right, pos.y - 1}};
	for (uint8_t i = 0; i < 4; i++)
	{
		if (Ai2ValidPos(positions[i]) == false)
			continue ;
		if (moveMap[positions[i].y][positions[i].x] == TOOL_MAP_BLOCKER)
			continue ;
		int plus = 2;
		int height = gameState.battle.ground->map[positions[i].y][positions[i].x].height;
		if (height > currentHeight)
			plus = (2 + (height - currentHeight));
		else if (height < currentHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= targetMoves)
		{
			if (moveMap[positions[i].y][positions[i].x] > temp)
			{
				moveMap[positions[i].y][positions[i].x] = temp;
				Ai2IterMoveMap(moveMap, temp, targetMoves, positions[i]);
			}
		}
	}
}

static void SetBlockedPositins(uint16_t **moveMap, t_AiCharacter **charQ, t_AiMapItem **items)
{
	for (int i = 0; charQ[i] != NULL; i++)
	{
		SDL_Point pos = charQ[i]->position;
		moveMap[pos.y][pos.x] = TOOL_MAP_BLOCKER;
	}
	for (int i = 0; items[i] != NULL; i++)
	{
		if (items[i]->type == SMOKE_BOMB)
			continue ;
		SDL_Point pos = items[i]->position;
		moveMap[pos.y][pos.x] = TOOL_MAP_BLOCKER;
	}
}

void GetAi2MapMovables(uint16_t **moveMap, SDL_Point pos, int moves, t_AiCharacter **charQ, t_AiMapItem **items)
{
	for (uint8_t i = 0; i < gameHeight; i++)
	{
		for (uint8_t j = 0; j < gameWidth; j++)
		{
			moveMap[i][j] = TOOL_MAP_SIGN;
			if (gameState.battle.ground->map[i][j].obj != NULL)
				moveMap[i][j] = TOOL_MAP_BLOCKER;
		}
	}
	SetBlockedPositins(moveMap, charQ, items);
	moveMap[pos.y][pos.x] = 0;
	Ai2IterMoveMap(moveMap, 0, moves, pos);
}

void AiIterator2::IterateMap()
{
	for (uint8_t i = 0; i < gameHeight; i++)
	{
		for (uint8_t j = 0; j < gameWidth; j++)
		{
			MoveToPosition(j, i);
			AbilityToPosition(j, i);
		}
	}
}

static int GetSizeForShit(t_AiCharacter **charQ)
{
	int index = 0;
	while (charQ[index] != NULL)
		index++;
	return (index);
}

void AddToTheAiMoves(t_Ai2MoveSaver &saver, t_MoverSmover add, bool ally)
{
	float min = saver.smalles;
	int index = saver.smallesIndex;
	if (!ally && add.score >= min)
		return ;
	else if (ally && add.score <= min)
		return ;
	saver.moves[index] = add;
	float newSmallest = (!ally) ? -9999999.0f : 9999999.0f;
	int newIndex = 0;
	for (int i = 0; i < SCORE_SAVE_SIZE; i++)
	{
		float score = saver.moves[i].score;
		if (!ally && score > newSmallest)
		{
			newSmallest = score;
			newIndex = i;
		}
		else if (ally && score < newSmallest)
		{
			newSmallest = score;
			newIndex = i;
		}
	}
	saver.smalles = newSmallest;
	saver.smallesIndex = newIndex;
}

void AiIterator2::CreateSavedMoves()
{
	int sizer = current->character->abilities.size() + 1;
	savedMoves = (t_Ai2MoveSaver*)malloc(sizeof(t_Ai2MoveSaver) * sizer);
	float smallest = (!ally) ? 100000.0f : -100000.0f;
	for (int i = 0; i < sizer; i++)
	{
		savedMoves[i].smallesIndex = 0;
		savedMoves[i].smalles = smallest;
		for (int j = 0; j < SCORE_SAVE_SIZE; j++)
			savedMoves[i].moves[j] = {{0, 0}, 0, smallest};
	}
	size = sizer;
}

void AiIterator2::CalculateMoves(t_AiCharacter *current, t_AiCharacter **charQ, t_AiMapItem **mapItems)
{
	ally = current->character->ally;
	int moves = (current->statuses.slowed != 0) ? current->moves / 2 : current->moves;
	AiIterator2::current = current;
	AiIterator2::charQ = charQ;
	AiIterator2::mapItems = mapItems;
	movables = CreateMoveMapForAi2(); //185.312600
	CreateSavedMoves(); //84.416900
	GetAi2MapMovables(movables, current->position, moves, charQ, mapItems);
	IterateMap();
	DestroyMoveMap2(movables); //115.798400
	free(savedMoves);
}
