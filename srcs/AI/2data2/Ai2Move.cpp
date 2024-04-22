
#include "../../../hdr/global.h"

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

static SDL_Point Ai2GetNextSmalles(uint16_t **map, uint8_t x, uint8_t y)
{
	SDL_Point pos = {(int)x, (int)y};
	int left = Ai2GetXToLeft(pos);
	int right = Ai2GetXToRight(pos);
	uint16_t current = map[y][x];
	SDL_Point positions[4] = {{left, pos.y + 1}, {left, pos.y - 1}, {right, pos.y + 1}, {right, pos.y - 1}};
	for (uint8_t i = 0; i < 4; i++)
	{
		if (AiValidPos(positions[i]) == false)
			continue ;
		uint16_t value = map[positions[i].y][positions[i].x];
		if (value < current)
		{
			current = value;
			pos = positions[i];
		}
	}
	return (pos);
}

void AiIterator2::MoveToPosition(uint8_t x, uint8_t y)
{
	if (movables[y][x] == TOOL_MAP_SIGN)
		return ;
	
}
