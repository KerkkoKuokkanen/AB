
#include "../../hdr/global.h"

void BattleGround::MoveInit(SDL_Renderer *rend)
{
	static SDL_Texture *point = get_texture(rend, "sprites/ground/pointIdicator.png");
	static SDL_Texture *line = get_texture(rend, "sprites/ground/line.png");
	moveInd = point;
	lineInd = line;
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
		moveIndicators[i]->orderLayer = 1;
		moveLines[i]->Deactivate();
	}
}

void BattleGround::CreateNewIndicator()
{
	SDL_Rect tempDest = {0, 0, 1000, 1000};
	Sprite *point = new Sprite(moveInd, tempDest, NULL, NULL, 0, FLIP_NONE);
	point->orderLayer = 1;
	moveIndicators.push_back(point);
	gameState.render->AddSprite(moveIndicators[moveIndicators.size() - 1], LINE_LAYER);
	moveIndicators[moveIndicators.size() - 1]->Deactivate();
	moveIndicators[moveIndicators.size() - 1]->orderLayer = 1;
}

bool BattleGround::BlockMouseHover(SDL_Point &position)
{
	if (position.x < 0 || position.y < 0 || position.x >= map[0].size() || position.y >= map.size())
		return (false);
	int index = position.y * map[0].size() + position.x;
	SDL_Rect dest = sprites[index][sprites[index].size() - 1].dest;
	SDL_Point target = {gameState.keys.mouseX, gameState.keys.mouseY};
	SDL_Point up = {dest.x + (gameState.battle.xDist / 2), dest.y - 250};
	SDL_Point left = {dest.x - 500, dest.y + 1700};
	SDL_Point down = {up.x, dest.y + 4000};
	SDL_Point right = {dest.x + gameState.battle.xDist + 350, left.y};
	return (CheckInsideShape(up, left, down, right, target));
}

bool BattleGround::MarkBlock(SDL_Point position)
{
	int index = position.y * map[0].size() + position.x;
	if (!map[position.y][position.x].active)
	{
		map[position.y][position.x].marked = false;
		return (false);
	}
	if (map[position.y][position.x].character != NULL)
	{
		if (map[position.y][position.x].character->killed)
		{
			map[position.y][position.x].marked = false;
			return (false);
		}
	}
	if (BlockMouseHover(position) && !HoverOverCheck(position) && !gameState.updateObjs.hover.overAnything)
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

void BattleGround::TakeMarkerAndPlaceIt(SDL_Point pos)
{
	int index = pos.y * map[0].size() + pos.x;
	SDL_Rect dest = sprites[index][sprites[index].size() - 1].dest;
	Vector place((float)(dest.x + 2400), (float)(dest.y + 1000));
	int i = 0;
	while (i < moveIndicators.size())
	{
		if (moveIndicators[i]->getStatus() == false)
			break ;
		i++;
	}
	if (i == moveIndicators.size())
	{
		CreateNewIndicator();
		i = moveIndicators.size() - 1;
	}
	moveIndicators[i]->Position(place);
	moveIndicators[i]->Activate();
}

void BattleGround::SetAiMoveAction(SDL_Point target, SDL_Point start)
{
	Character *used = map[start.y][start.x].character;
	SetMovables(used);
	std::vector<SDL_Point> positions = FindPath(start, target);
	ClearMovables();
	setMoved(positions, true);
}

void BattleGround::MarkerControl(SDL_Point cPos, SDL_Point mPos)
{
	markingPath = false;
	ResetIndicators();
	if (map[cPos.y][cPos.x].character->turn == false || map[cPos.y][cPos.x].character->ally == false)
		return ;
	std::vector<SDL_Point> positions = FindPath(cPos, mPos);
	if (positions.size() <= 1)
	{
		positions.clear();
		return ;
	}
	for (int i = 0; i < positions.size(); i++)
	{
		int index = positions[i].y * map[0].size() + positions[i].x;
		sprites[index][sprites[index].size() - 1].ColorMod(195, 255, 195);
		TakeMarkerAndPlaceIt(positions[i]);
		if (i != 0)
			TakeLineAndPlaceIt(positions[i - 1], positions[i]);
	}
	gameState.updateObjs.UI->ShowEnergy(toolMap[positions[0].y][positions[0].x], true);
	setMoved(positions);
	positions.clear();
	markingPath = true;
}

bool BattleGround::NoOtherCharacters()
{
	for (int i = 0; i < characters.size(); i++)
	{
		if (characters[i].character->clicked)
			return (false);
	}
	return (true);
}

void BattleGround::PlaceMarker()
{
	if (gameState.updateObjs.hover.overAnything || gameState.updateObjs.abilities->active)
	{
		ResetIndicators();
		return ;
	}
	SDL_Point marked = {0, 0};
	SDL_Point characterBlock = {0, 0};
	bool visit1 = false, visit2 = false;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (map[i][j].character != NULL && map[i][j].marked && gameState.keys.click == RELEASE_CLICK &&
				!gameState.updateObjs.turnOrder->stuffHappening && map[i][j].additional.object == NULL)
			{
				if (NoOtherCharacters() == false)
				{
					for (int k = 0; k < characters.size(); k++)
						characters[k].character->clicked = false;
				}
				map[i][j].character->clicked = true;
				SetMovables(map[i][j].character);
			}
			if (map[i][j].character != NULL && map[i][j].character->clicked && !map[i][j].character->killed)
			{
				characterBlock = {j, i};
				visit1 = true;
			}
			if (map[i][j].marked && map[i][j].highlited)
			{
				marked = {j, i};
				visit2 = true;
			}
		}
	}
	if (visit1 && visit2)
		MarkerControl(characterBlock, marked);
	else
		ResetIndicators();
}

void BattleGround::CheckMarkedBlocks(std::vector<SDL_Point> &marked)
{
	if (marked.size() == 0)
		return ;
	if (gameState.updateObjs.hover.overAnything)
		return ;
	if (gameState.updateObjs.turnOrder->stuffHappening)
		return ;
	if (marked.size() == 1)
	{
		if (map[marked[0].y][marked[0].x].character == NULL || map[marked[0].y][marked[0].x].highlited ||
			gameState.updateObjs.abilities->active)
			return ;
		int index = marked[0].y * map[0].size() + marked[0].x;
		if (map[marked[0].y][marked[0].x].character->ally)
			sprites[index][sprites[index].size() - 1].ColorMod(120, 255, 100);
		else
			sprites[index][sprites[index].size() - 1].ColorMod(255, 69, 56);
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
	if (map[block.y][block.x].character == NULL || map[block.y][block.x].highlited ||
		gameState.updateObjs.abilities->active)
		return ;
	int index = block.y * map[0].size() + block.x;
	if (map[block.y][block.x].character->ally)
		sprites[index][sprites[index].size() - 1].ColorMod(120, 255, 100);
	else
		sprites[index][sprites[index].size() - 1].ColorMod(255, 69, 56);
}

void BattleGround::CheckBlocked(int i, int j)
{
	map[i][j].blocked = false;
	if (map[i][j].character != NULL)
		map[i][j].blocked = true;
}

void BattleGround::IterBlocks()
{
	std::vector<SDL_Point> markedBlocks;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			int index = i * map[0].size() + j;
			sprites[index][sprites[index].size() - 1].ClearColorMod();
			SDL_Point pos = {j, i};
			if (MarkBlock(pos))
				markedBlocks.push_back(pos);
			if (map[i][j].highlited != 0)
			{
				int index = i * map[0].size() + j;
				ColorFade(&sprites[index][sprites[index].size() - 1], map[i][j].highlited);
			}
			//CheckBlocked(i, j);
		}
	}
	CheckMarkedBlocks(markedBlocks);
	PlaceMarker();
	markedBlocks.clear();
}

void BattleGround::ColorFade(Sprite *sprite, int sign)
{
	if (sign == 1)
	{
		float r = 107.0f - 104.0f;
		float g = 255.0f - 196.0f;
		float b = 122 - 113.0f;
		float fadeMulti = cos(gameState.updateObjs.fadeIter) / 2.0f + 0.5f;
		sprite->ColorMod(104 + (int)(r * fadeMulti), 196 + (int)(g * fadeMulti), 113 + (int)(b * fadeMulti));
		return ;
	}
	float r = 255.0f - 184.0f;
	float g = 106.0f - 83.0f;
	float b = 106.0f - 83.0f;
	float fadeMulti = cos(gameState.updateObjs.fadeIter) / 2.0f + 0.5f;
	sprite->ColorMod(184 + (int)(r * fadeMulti), 83 + (int)(g * fadeMulti), 83 + (int)(b * fadeMulti));
}
