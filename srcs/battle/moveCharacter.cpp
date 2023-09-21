
#include "../../hdr/global.h"

void BattleGround::setMoved(std::vector<SDL_Point> &path)
{
	if (gameState.keys.click != RELEASE_CLICK)
		return ;
	movedCharacter.path.clear();
	for (int i = path.size() - 1; i >= 0; i--)
		movedCharacter.path.push_back(path[i]);
	movedCharacter.character = map[movedCharacter.path[0].y][movedCharacter.path[0].x].character;
	movedCharacter.index = 0;
	movedCharacter.iterator = 0;
	movedCharacter.character->clicked = false;
	movedCharacter.character->moving = true;
	movedCharacter.character->sprite->ClearAlphaMod();
	movedCharacter.character->stand->ClearAlphaMod();
	map[movedCharacter.path[0].y][movedCharacter.path[0].x].blocked = false;
	map[movedCharacter.path[0].y][movedCharacter.path[0].x].character = NULL;
}

Vector BattleGround::GetCharacterCoord(SDL_Point pos, Character *character)
{
	if (pos.x < 0 || pos.y < 0 || pos.y >= map.size() || pos.x >= map[pos.y].size())
		printf("Battleground: position out of bounds\n");
	int index = pos.y * map[0].size() + pos.x;
	SDL_Rect location = sprites[index][sprites[index].size() - 1].dest;
	Vector place((float)location.x, (float)location.y);
	switch (character->cSing)
	{
		case THIEF:
			place.x += 175.0f;
			place.y = place.y - (float)character->getHeight() + (float)gameState.battle.yDist / 2.0f - 300;
			break ;
		case SKELE:
			place.x -= 500.0f;
			place.y = place.y - (float)character->getHeight() + (float)gameState.battle.yDist / 2.0f + 550;
			break ;
		case PYRO:
			place.x -= 500.0f;
			place.y -= 5350.0f;
			break ;
		case LION:
			place.x -= 400.0f;
			place.y -= 5650.0f;
			break ;
		case SMITH:
			place.x += 10.0f;
			place.y -= 4850.0f;
			break ;
		case MAGE:
			place.x -= 240.0f;
			place.y -= 5350.0f;
			break ;
	}
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

bool BattleGround::MovingLeft(SDL_Point curr, SDL_Point next)
{
	if (next.x < curr.x)
		return (true);
	if (curr.y % 2 != 0 && next.x == curr.x)
		return true;
	return (false);
}

void BattleGround::AddDust(SDL_Point curr, SDL_Point next)
{
	if (movedCharacter.iterator != 4)
		return ;
	Mix_SetPanning(0, MIX_MAX_VOLUME, MIX_MAX_VOLUME);
	PlaySound(gameState.audio.TFootStep[rand() % 3], Channels::THIEF_STEP_CHANNEL, 0);
	int index = curr.y * map[0].size() + curr.x;
	SDL_Rect dest = sprites[index][sprites[index].size() - 1].dest;
	SDL_Point pos = {dest.x + 2500, dest.y + 1500};
	if (MovingLeft(curr, next))
	{
		Vector dir(1.0f, 0.0f);
		CreateDust(pos, dir);
		return ;
	}
	Vector dir(-1.0f, 0.0f);
	CreateDust(pos, dir);
}

Vector BattleGround::GetPlaceWithIterator(Vector ogPos, Vector newPos, float unit, Vector highPoint, SDL_Point curr, SDL_Point next)
{
	Vector place(0, 0);
	float angle = (movedCharacter.iterator < 14) ? 7.0f : 0.0f;
	float sign = 1.0f;
	if (MovingLeft(curr, next))
	{
		sign = (-1.0f);
		angle = (movedCharacter.iterator < 14) ? -7.0f : 0.0f;
	}
	if (movedCharacter.iterator < 14)
	{
		angle = angle - ((0.538f * (float)movedCharacter.iterator) * sign);
		movedCharacter.character->sprite->setAngle(angle);
		movedCharacter.character->stand->setAngle(angle);
		int index = curr.y * map[0].size() + curr.x;
		if (movedCharacter.character->ally)
			sprites[index][sprites[index].size() - 1].ColorMod(195, 255, 195);
		else
			sprites[index][sprites[index].size() - 1].ColorMod(255, 181, 181);
		place = ParabolaPosition(ogPos, highPoint, unit, ogPos.x);
	}
	else
	{
		angle = angle - ((0.538f * ((float)movedCharacter.iterator - 14.0f)) * sign);
		movedCharacter.character->sprite->setAngle(angle);
		movedCharacter.character->stand->setAngle(angle);
		int index = next.y * map[0].size() + next.x;
		if (movedCharacter.character->ally)
			sprites[index][sprites[index].size() - 1].ColorMod(195, 255, 195);
		else
			sprites[index][sprites[index].size() - 1].ColorMod(255, 181, 181);
		if (movedCharacter.iterator == 15)
		{
			movedCharacter.character->sprite->orderLayer = next.y;
			movedCharacter.character->stand->orderLayer = next.y;
			movedCharacter.character->sprite->setDepth(map[next.y][next.x].height * BATTLE_DEPTH_UNIT + 8);
			movedCharacter.character->stand->setDepth(map[next.y][next.x].height * BATTLE_DEPTH_UNIT + 7);
		}
		place = ParabolaPosition(newPos, highPoint, unit, ogPos.x);
	}
	return (place);
}

void BattleGround::MangeIterator(Vector newPos)
{
	if (movedCharacter.iterator >= 28)
	{
		movedCharacter.iterator = 0;
		movedCharacter.index += 1;
		if ((movedCharacter.index + 1) >= movedCharacter.path.size())
		{
			PlaceCharacter(movedCharacter.path[movedCharacter.path.size() - 1], movedCharacter.character);
			map[movedCharacter.path[movedCharacter.path.size() - 1].y][movedCharacter.path[movedCharacter.path.size() - 1].x].highlited = 0;
			movedCharacter.character->sprite->setAngle(0.0f);
			movedCharacter.character->stand->setAngle(0.0f);
			movedCharacter.character->moving = false;
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
	if (movedCharacter.character->killed)
	{
		movedCharacter.character = NULL;
		return ;
	}
	SDL_Point curr = movedCharacter.path[movedCharacter.index];
	SDL_Point next = movedCharacter.path[movedCharacter.index + 1];
	AddDust(curr, next);
	Vector ogPos = GetCharacterCoord(curr, movedCharacter.character);
	Vector newPos = GetCharacterCoord(next, movedCharacter.character);
	float highValue = (ogPos.y < newPos.y) ? ogPos.y : newPos.y;
	Vector highPoint(ogPos.x + (newPos.x - ogPos.x) / 2.0f, highValue - 1250.0f);
	float unit = (newPos.x - ogPos.x) / 28.0f;
	Vector place = GetPlaceWithIterator(ogPos, newPos, unit, highPoint, curr, next);
	movedCharacter.character->Position(place);
	MangeIterator(newPos);
}

void BattleGround::CancelMovement(SDL_Point pos)
{
	if (movedCharacter.character == NULL)
		return ;
	movedCharacter.character->sprite->setAngle(0);
	movedCharacter.character->stand->setAngle(0);
	movedCharacter.character->moving = false;
	movedCharacter.character->clicked = false;
	movedCharacter.index = (-1);
	PlaceCharacter(pos, movedCharacter.character);
	movedCharacter.character = NULL;
	movedCharacter.path.clear();
}
