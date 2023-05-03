
#include "../../hdr/global.h"

void BattleGround::setMoved(std::vector<SDL_Point> &path)
{
	if (gameState.keys.click != 1)
		return ;
	movedCharacter.path.clear();
	for (int i = path.size() - 1; i >= 0; i--)
		movedCharacter.path.push_back(path[i]);
	movedCharacter.character = map[movedCharacter.path[0].y][movedCharacter.path[0].x].character;
	movedCharacter.index = 0;
	movedCharacter.iterator = 0;
	movedCharacter.character->clicked = false;
	movedCharacter.character->sprite->ClearAlphaMod();
	map[movedCharacter.path[0].y][movedCharacter.path[0].x].character = NULL;
}

Vector BattleGround::GetCharacterCoord(SDL_Point pos, Character *character)
{
	if (pos.x < 0 || pos.y < 0 || pos.y >= map.size() || pos.x >= map[pos.y].size())
		printf("Battleground: position out of bounds\n");
	int index = pos.y * map[0].size() + pos.x;
	SDL_Rect location = sprites[index][sprites[index].size() - 1].dest;
	Vector place((float)location.x, (float)location.y);
	int height = character->getHeight();
	place.y = place.y - (float)height + (float)gameState.battle.yDist / 2.0f - 450;
	return (place);
}

Vector BattleGround::ParabolaPosition(Vector pos, Vector highPoint, float unit, float ogX)
{
	float h = highPoint.x;
	float k = highPoint.y;
	float plusMinus = (k - pos.y) * (-1.0f);
	float brackets = (pos.x - h) * (pos.x - h);
	float a = plusMinus / brackets;
	float x = ogX + (unit * movedCharacter.iterator);
	return (Vector(x, a * (x - h) * (x - h) + k));
}

Vector BattleGround::GetPlaceWithIterator(Vector ogPos, Vector newPos, float unit, Vector highPoint, SDL_Point curr, SDL_Point next)
{
	Vector place(0, 0);
	if (movedCharacter.iterator < 14)
	{
		int index = curr.y * map[0].size() + curr.x;
		sprites[index][sprites[index].size() - 1].ColorMod(195, 255, 195);
		place = ParabolaPosition(ogPos, highPoint, unit, ogPos.x);
	}
	else
	{
		int index = next.y * map[0].size() + next.x;
		sprites[index][sprites[index].size() - 1].ColorMod(195, 255, 195);
		if (movedCharacter.iterator >= 15)
			movedCharacter.character->sprite->orderLayer = next.y * 2 + 1;
		place = ParabolaPosition(newPos, highPoint, unit, ogPos.x);
	}
	return (place);
}

void BattleGround::MangeIterator(Vector newPos)
{
	if (movedCharacter.iterator == 28)
	{
		movedCharacter.iterator = 0;
		movedCharacter.index += 1;
		if ((movedCharacter.index + 1) >= movedCharacter.path.size())
		{
			PlaceCharacter(movedCharacter.path[movedCharacter.path.size() - 1], movedCharacter.character);
			movedCharacter.character = NULL;
			return ;
		}
		movedCharacter.character->Position(newPos);
		return ;
	}
	movedCharacter.iterator += 1;
}

void BattleGround::MoveCharacter()
{
	if (movedCharacter.character == NULL)
		return ;
	SDL_Point curr = movedCharacter.path[movedCharacter.index];
	SDL_Point next = movedCharacter.path[movedCharacter.index + 1];
	Vector ogPos = GetCharacterCoord(curr, movedCharacter.character);
	Vector newPos = GetCharacterCoord(next, movedCharacter.character);
	float highValue = (ogPos.y < newPos.y) ? ogPos.y : newPos.y;
	Vector highPoint(ogPos.x + (newPos.x - ogPos.x) / 2.0f, highValue - 1250.0f);
	float unit = (newPos.x - ogPos.x) / 28.0f;
	Vector place = GetPlaceWithIterator(ogPos, newPos, unit, highPoint, curr, next);
	movedCharacter.character->Position(place);
	MangeIterator(newPos);
}
