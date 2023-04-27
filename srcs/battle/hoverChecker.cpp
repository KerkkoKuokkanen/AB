
#include "../../hdr/global.h"

bool BattleGround::CheckOverPositions(std::vector<SDL_Point> &positions, SDL_Point og)
{
	static int p = 0;
	p++;
	if (positions.size() <= 1)
		return (false);
	for (int i = 0; i < positions.size(); i++)
	{
		int index = positions[i].y * map[0].size() + positions[i].x;
		SDL_Rect dest = sprites[index][sprites[index].size() - 1].dest;
		SDL_Rect target = {dest.x - 80, dest.y + 1500, gameState.battle.xDist + 100, 100000};
		SDL_Point mouse = {gameState.keys.mouseX, gameState.keys.mouseY};
		if (pointCheck(mouse, target) || BlockMouseHover(positions[i]))
			return (true);
	}
	return (false);
}

bool BattleGround::HoverOverCheck(SDL_Point ogPos)
{
	if (ogPos.y >= (map.size() - 1))
		return (false);
	std::vector<SDL_Point> overBlocks;
	int index = ogPos.y * map[0].size() + ogPos.x;
	int ogH = map[ogPos.y][ogPos.x].height;
	SDL_Rect ogDest = sprites[index][sprites[index].size() - 1].dest;
	for (int i = ogPos.y + 1; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (map[i][j].height > ogH && map[i][j].active)
			{
				index = i * map[0].size() + j;
				for (int k = map[i][j].height; k > ogH; k--)
				{
					SDL_Rect tester = sprites[index][k].dest;
					if (boxCheck(ogDest, tester))
					{
						SDL_Point adder = {j, i};
						overBlocks.push_back(adder);
						break ;
					}
				}
			}
		}
	}
	bool ret = CheckOverPositions(overBlocks, ogPos);
	overBlocks.clear();
	return (ret);
}
