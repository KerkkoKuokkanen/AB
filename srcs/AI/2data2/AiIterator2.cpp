
#include "../../../hdr/global.h"

uint8_t gameWidth = 0;
uint8_t gameHeight = 0;

void InitAiIteration()
{
	int w = gameState.battle.ground->map[0].size();
	int h = gameState.battle.ground->map.size();
	gameWidth = (uint8_t)w;
	gameHeight = (uint8_t)h;
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

static uint16_t **CreateMoveMap()
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

static void DestroyMoveMap(uint16_t **map)
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

static void GetAiMapMovables(uint16_t **moveMap, t_AiCharacter *character)
{
	int moves = (character->statuses.slowed != 0) ? character->moves / 2 : character->moves;
	for (uint8_t i = 0; i < gameHeight; i++)
	{
		for (uint8_t j = 0; j < gameWidth; j++)
			moveMap[i][j] = TOOL_MAP_SIGN;
	}
	moveMap[character->position.y][character->position.x] = 0;
	Ai2IterMoveMap(moveMap, 0, moves, character->position);
}

void AiIterator2::IterateMap()
{
	for (uint8_t i = 0; i < gameHeight; i++)
	{
		for (uint8_t j = 0; j < gameWidth; j++)
		{
			MoveToPosition(j, i);
		}
	}
}

void AiIterator2::CalculateMoves(t_AiCharacter *current, t_AiCharacter **charQ, t_AiMapItem **mapItems)
{
	AiIterator2::current = current;
	AiIterator2::charQ = charQ;
	AiIterator2::mapItems = mapItems;
	movables = CreateMoveMap();
	GetAiMapMovables(movables, current);
	IterateMap();
	DestroyMoveMap(movables);
}
