
#include "../../hdr/global.h"

void GroundColoring::Update()
{
	if (!active)
		return ;
	float fadeMulti = cos(gameState.updateObjs.fadeIter) / 2.0f + 0.5f;
	for (int i = 0; i < spriteMap.size(); i++)
	{
		for (int j = 0; j < spriteMap[0].size(); j++)
		{
			if (!spriteMap[i][j].colored)
			{
				spriteMap[i][j].sprite->ClearColorMod();
				continue ;
			}
			if (fade)
			{
				float r = spriteMap[i][j].rh - spriteMap[i][j].rl;
				float g = spriteMap[i][j].gh - spriteMap[i][j].gl;
				float b = spriteMap[i][j].bh - spriteMap[i][j].bl;
				Uint8 red = (int)spriteMap[i][j].rl + (int)(r * fadeMulti);
				Uint8 green = (int)spriteMap[i][j].gl + (int)(g * fadeMulti);
				Uint8 blue = (int)spriteMap[i][j].bl + (int)(b * fadeMulti);
				spriteMap[i][j].sprite->ColorMod(red, green, blue);
			}
			else
				spriteMap[i][j].sprite->ColorMod((Uint8)spriteMap[i][j].rh, (Uint8)spriteMap[i][j].gh, (Uint8)spriteMap[i][j].bh);
		}
	}
}

void GroundColoring::SetColoredPosition(SDL_Point pos, Color &high, Color &low)
{
	spriteMap[pos.y][pos.x].rh = high.r;
	spriteMap[pos.y][pos.x].gh = high.g;
	spriteMap[pos.y][pos.x].bh = high.b;
	spriteMap[pos.y][pos.x].rl = low.r;
	spriteMap[pos.y][pos.x].gl = low.g;
	spriteMap[pos.y][pos.x].bl = low.b;
	spriteMap[pos.y][pos.x].colored = true;
}

void GroundColoring::SetColoredPosition(SDL_Point pos, Color &color)
{
	spriteMap[pos.y][pos.x].rh = color.r;
	spriteMap[pos.y][pos.x].gh = color.g;
	spriteMap[pos.y][pos.x].bh = color.b;
	spriteMap[pos.y][pos.x].colored = true;
}

void GroundColoring::SetColoredPositions(std::vector<SDL_Point> &positions, Color &high, Color &low)
{
	for (int i = 0; i < positions.size(); i++)
	{
		SDL_Point pos = positions[i];
		spriteMap[pos.y][pos.x].rh = high.r;
		spriteMap[pos.y][pos.x].gh = high.g;
		spriteMap[pos.y][pos.x].bh = high.b;
		spriteMap[pos.y][pos.x].rl = low.r;
		spriteMap[pos.y][pos.x].gl = low.g;
		spriteMap[pos.y][pos.x].bl = low.b;
		spriteMap[pos.y][pos.x].colored = true;
	}
}

void GroundColoring::SetColoredPositions(std::vector<SDL_Point> &positions, Color &color)
{
	for (int i = 0; i < positions.size(); i++)
	{
		SDL_Point pos = positions[i];
		spriteMap[pos.y][pos.x].rh = color.r;
		spriteMap[pos.y][pos.x].gh = color.g;
		spriteMap[pos.y][pos.x].bh = color.b;
		spriteMap[pos.y][pos.x].colored = true;
	}
}

void GroundColoring::ClearPosition(SDL_Point pos)
{
	spriteMap[pos.y][pos.x].sprite->ClearColorMod();
	spriteMap[pos.y][pos.x].colored = false;
}

void GroundColoring::ClearMap()
{
	for (int i = 0; i < spriteMap.size(); i++)
	{
		for (int j = 0; j < spriteMap[0].size(); j++)
		{
			spriteMap[i][j].sprite->ClearColorMod();
			spriteMap[i][j].colored = false;
		}
	}
}

void GroundColoring::SetMap()
{
	std::vector<t_CMap> add;
	t_CMap unit = {NULL, 0, 0, 0, 0, 0, 0, false};
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		spriteMap.push_back(add);
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			SDL_Point pos = {j, i};
			unit.sprite = gameState.battle.ground->GetSprite(pos);
			spriteMap[i].push_back(unit);
		}
	}
}
