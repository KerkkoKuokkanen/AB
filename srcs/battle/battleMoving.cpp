
#include "../../hdr/global.h"

void BattleGround::MoveInit(SDL_Renderer *rend)
{
	static SDL_Texture *point = get_texture(rend, "sprites/ground/pointIdicator.png");
	static SDL_Texture *line = get_texture(rend, "sprites/ground/line.png");
	SDL_Rect tempDest = {0, 0, 5000, 250};
	SDL_Rect indDest = {-5000, 0, 1000, 1000};
	Sprite sPoint(point, indDest, NULL, NULL, 0, FLIP_NONE);
	Sprite sLine(line, tempDest, NULL, NULL, 0, FLIP_NONE);
	for (int i = 0; i < 20; i++)
	{
		moveIndicators.push_back(new Sprite(sPoint));
		moveLines.push_back(new Sprite(sLine));
		gameState.render->AddSprite(moveIndicators[i], layer + 1);
		gameState.render->AddSprite(moveLines[i], layer + 1);
		moveIndicators[i]->Deactivate();
		moveLines[i]->Deactivate();
	}
}

bool BattleGround::BlockMouseHover(SDL_Point &position)
{
	if (position.x < 0 || position.y < 0 || position.x >= map[0].size() || position.y >= map.size())
		return (false);
	int index = position.y * map[0].size() + position.x;
	SDL_Rect dest = sprites[index][sprites[index].size() - 1].dest;
	SDL_Point target = {gameState.keys.mouseX, gameState.keys.mouseY};
	SDL_Point up = {dest.x + (gameState.battle.xDist / 2), dest.y};
	SDL_Point left = {dest.x - 80, dest.y + 1500};
	SDL_Point down = {up.x, dest.y + 3300};
	SDL_Point right = {dest.x + gameState.battle.xDist + 100, left.y};
	return (CheckInsideShape(up, left, down, right, target));
}

bool BattleGround::MarkBlock(SDL_Point position)
{
	int index = position.y * map[0].size() + position.x;
	if (!map[position.y][position.x].active)
		return (false);
	if (BlockMouseHover(position))
	{
		map[position.y][position.x].marked = true;
		return (true);
	}
	map[position.y][position.x].marked = false;
	return (false);
}

void BattleGround::ResetIndicators()
{
	for (int i = 0; i < moveIndicators.size(); i++)
		moveIndicators[i]->Deactivate();
	for (int i = 0; i < moveLines.size(); i++)
		moveLines[i]->Deactivate();
}

void BattleGround::MarkerControl(SDL_Point cPos, SDL_Point mPos)
{
	if (cPos.x == mPos.x && cPos.y == mPos.y)
	{
		ResetIndicators();
		return ;
	}
	int index = mPos.y * map[0].size() + mPos.x;
	SDL_Rect dest = sprites[index][sprites[index].size() - 1].dest;
	Vector place((float)(dest.x + 2400), (float)(dest.y + 1000));
	moveIndicators[0]->Position(place);
	moveIndicators[0]->Activate();
}

void BattleGround::PlaceMarker()
{
	SDL_Point *marked = NULL;
	SDL_Point *characterBlock = NULL;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (map[i][j].character != NULL && map[i][j].character->clicked)
			{
				SDL_Point pos = {j, i};
				characterBlock = &pos;
			}
			if (map[i][j].marked && map[i][j].highlited)
			{
				SDL_Point pos = {j, i};
				marked = &pos;
			}
		}
	}
	if (marked != NULL && characterBlock != NULL)
		MarkerControl(*characterBlock, *marked);
	else
		ResetIndicators();
}

void BattleGround::CheckMarkedBlocks(std::vector<SDL_Point> &marked)
{
	if (marked.size() == 0)
		return ;
	if (marked.size() == 1)
	{
		if (map[marked[0].y][marked[0].x].character == NULL || map[marked[0].y][marked[0].x].highlited)
			return ;
		int index = marked[0].y * map[0].size() + marked[0].x;
		sprites[index][sprites[index].size() - 1].ColorMod(120, 255, 100);
		return ;
	}
	SDL_Point block = marked[0];
	for (int i = 0; i < marked.size(); i++)
	{
		if (marked[i].y > block.y)
		{
			map[block.y][block.x].marked = false;
			block = marked[i];
		}
		else if (marked[i].x > block.x)
		{
			map[block.y][block.x].marked = false;
			block = marked[i];
		}
	}
	if (map[block.y][block.x].character == NULL || map[block.y][block.x].highlited)
		return ;
	int index = block.y * map[0].size() + block.x;
	sprites[index][sprites[index].size() - 1].ColorMod(120, 255, 100);
}

void BattleGround::IterBlocks()
{
	std::vector<SDL_Point> markedBlocks;
	static float fadeIter = 0.0f;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			int index = i * map[0].size() + j;
			sprites[index][sprites[index].size() - 1].ClearColorMod();
			SDL_Point pos = {j, i};
			if (MarkBlock(pos))
				markedBlocks.push_back(pos);
			if (map[i][j].highlited)
			{
				int index = i * map[0].size() + j;
				ColorFade(&sprites[index][sprites[index].size() - 1], fadeIter);
			}
		}
	}
	CheckMarkedBlocks(markedBlocks);
	PlaceMarker();
	markedBlocks.clear();
	fadeIter += 0.1f;
	if (fadeIter >= 44.0f)
		fadeIter = 0.0f;
}

void BattleGround::ColorFade(Sprite *sprite, float fadeIter)
{
	float r = 107.0f - 104.0f;
	float g = 255.0f - 196.0f;
	float b = 122 - 113.0f;
	float fadeMulti = cos(fadeIter) / 2.0f + 0.5f;
	sprite->ColorMod(104 + (int)(r * fadeMulti), 196 + (int)(g * fadeMulti), 113 + (int)(b * fadeMulti));
}

void BattleGround::ClearMovables()
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j].highlited)
				map[i][j].highlited = false;
		}
	}
}

void BattleGround::SetMovables(Character *character)
{
	SDL_Point pos = character->getCoord();
	map[pos.y][pos.x].highlited = true;
	IterMapMovables(pos, 0, character->moves);
}

void BattleGround::IterMapMovables(SDL_Point pos, int moves, int cMoves)
{
	if (moves >= cMoves)
		return ;
	int currHeight = map[pos.y][pos.x].height;
	int modder = (pos.y % 2 == 0) ? (-1) : 1;
	int sizeModder = map[0].size() - 1;
	if (pos.y > 0)
	{
		int plus = 2;
		if (map[pos.y - 1][pos.x].height > currHeight)
			plus = 2 + (map[pos.y - 1][pos.x].height - currHeight);
		else if (map[pos.y - 1][pos.x].height < currHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			map[pos.y - 1][pos.x].highlited = true;
			SDL_Point location = {pos.x, pos.y - 1};
			IterMapMovables(location, temp, cMoves);
		}
	}
	if (pos.y < (map.size() - 1))
	{
		int plus = 2;
		if (map[pos.y + 1][pos.x].height > currHeight)
			plus = 2 + (map[pos.y + 1][pos.x].height - currHeight);
		else if (map[pos.y + 1][pos.x].height < currHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			map[pos.y + 1][pos.x].highlited = true;
			SDL_Point location = {pos.x, pos.y + 1};
			IterMapMovables(location, temp, cMoves);
		}
	}
	if (pos.y > 0 && pos.x > 0 && pos.x < sizeModder)
	{
		int plus = 2;
		if (map[pos.y - 1][pos.x + modder].height > currHeight)
			plus = 2 + (map[pos.y - 1][pos.x + modder].height - currHeight);
		else if (map[pos.y - 1][pos.x + modder].height < currHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			map[pos.y - 1][pos.x + modder].highlited = true;
			SDL_Point location = {pos.x + modder, pos.y - 1};
			IterMapMovables(location, temp, cMoves);
		}
	}
	if (pos.y < (map.size() - 1) && pos.x > 0 && pos.x < sizeModder)
	{
		int plus = 2;
		if (map[pos.y + 1][pos.x + modder].height > currHeight)
			plus = 2 + (map[pos.y + 1][pos.x + modder].height - currHeight);
		else if (map[pos.y + 1][pos.x + modder].height < currHeight)
			plus = 1;
		int temp = moves + plus;
		if (temp <= cMoves)
		{
			map[pos.y + 1][pos.x + modder].highlited = true;
			SDL_Point location = {pos.x + modder, pos.y + 1};
			IterMapMovables(location, temp, cMoves);
		}
	}
}
