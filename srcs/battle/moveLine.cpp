
#include "../../hdr/global.h"

void BattleGround::CreateNewLine()
{
	SDL_Rect tempDest = {-5000, 0, 1000, 1000};
	Sprite *line = new Sprite(lineInd, tempDest, NULL, NULL, 0, FLIP_NONE);
	line->orderLayer = 0;
	moveLines.push_back(line);
	gameState.render->AddSprite(moveLines[moveLines.size() - 1], LINE_LAYER);
	moveLines[moveLines.size() - 1]->Deactivate();
}

int BattleGround::findLine()
{
	int i = 0;
	while (i < moveLines.size())
	{
		if (moveLines[i]->getStatus() == false)
			break ;
		i++;
	}
	if (i == moveLines.size())
		CreateNewLine();
	return (i);
}

void BattleGround::TakeLineAndPlaceIt(SDL_Point startPos, SDL_Point endPos)
{
	int index1 = startPos.y * map[0].size() + startPos.x;
	int index2 = endPos.y * map[0].size() + endPos.x;
	SDL_Rect dest1 = sprites[index1][sprites[index1].size() - 1].dest;
	SDL_Rect dest2 = sprites[index2][sprites[index2].size() - 1].dest;
	Vector place1((float)(dest1.x + 2900), (float)(dest1.y + 1375));
	Vector place2((float)(dest2.x + 2900), (float)(dest2.y + 1375));
	Vector vec(place1.x - place2.x, place1.y - place2.y);
	float len = vec.Magnitude();
	int index = findLine();
	int spriteWidth = rounding(len);
	float angle = (place2.y > place1.y) ? -vectorAngle(vec, Vector(1.0f, 0.0f)) : vectorAngle(vec, Vector(1.0f, 0.0f));
	float xPlace = (place2.x + (vec.x / 2.0f)) - (len / 2.0f);
	float yPlace = place2.y + (vec.y / 2.0f);
	moveLines[index]->setWidth(spriteWidth);
	moveLines[index]->Position(Vector(xPlace, yPlace));
	moveLines[index]->setAngle((double)degree(angle));
	moveLines[index]->Activate();
}
