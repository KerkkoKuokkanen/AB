
#include "../../../hdr/global.h"

static bool MovingLeft(SDL_Point curr, SDL_Point next)
{
	if (next.x < curr.x)
		return (true);
	if (curr.y % 2 != 0 && next.x == curr.x)
		return true;
	return (false);
}

static Vector ParabolaPosition(Vector pos, Vector highPoint, float unit, float ogX, int counter)
{
	float h = highPoint.x;
	float k = highPoint.y;
	float plusMinus = (k - pos.y) * (-1.0f);
	float brackets = (pos.x - h) * (pos.x - h);
	float a = plusMinus / brackets;
	float x = ogX + (unit * (float)counter);
	return (Vector(x, a * (x - h) * (x - h) + k));
}

Rotate::Rotate(Character *character, Character *target)
{
	if (target == NULL || character == NULL || target->killed || character->killed)
	{
		done = true;
		return ;
	}
	gameState.modes.disableBars = true;
	PlaySound(gameState.audio.TFootStep[rand() % 3], Channels::THIEF_STEP_CHANNEL, 0);
	PlaySound(gameState.audio.rotate, Channels::ROTATE, 0);
	Rotate::character = character;
	Rotate::target = target;
	character->sprite->ClearAlphaMod();
	character->stand->ClearAlphaMod();
	target->sprite->ClearAlphaMod();
	target->sprite->ClearAlphaMod();
	characterTarget = target->position;
	targetTarget = character->position;
	Vector cnp = gameState.battle.ground->GetCharacterCoord(characterTarget, character);
	cNewPos = {cnp.x, cnp.y};
	Vector tnp = gameState.battle.ground->GetCharacterCoord(targetTarget, target);
	tNewPos = {tnp.x, tnp.y};
	float chv = (character->position.y < characterTarget.y) ? (float)character->sprite->dest.y : cNewPos.y;
	Vector ccHighPoint((float)character->sprite->dest.x + (cNewPos.x - (float)character->sprite->dest.x) / 2.0f, chv - 1250.0f);
	cHighPoint = {ccHighPoint.x, ccHighPoint.y};
	float thv = (target->position.y < targetTarget.y) ? (float)target->sprite->dest.y : tNewPos.y;
	Vector ttHighPoint((float)target->sprite->dest.x + (tNewPos.x - (float)target->sprite->dest.x) / 2.0f, thv - 1250.0f);
	tHighPoint = {ttHighPoint.x, ttHighPoint.y};
	cUnit = (cNewPos.x - (float)character->sprite->dest.x) / 28.0f;
	tUnit = (tNewPos.x - (float)target->sprite->dest.x) / 28.0f;
	Vector ccOgPos = gameState.battle.ground->GetCharacterCoord(character->position, character);
	Vector ttOgPos = gameState.battle.ground->GetCharacterCoord(target->position, target);
	cOgPos = {ccOgPos.x, ccOgPos.y};
	tOgPos = {ttOgPos.x, ttOgPos.y};
	done = false;
	counter = 0;
}

Vector Rotate::GetCharacterWithIterator()
{
	Vector place(0, 0);
	float sign = (MovingLeft(character->position, characterTarget)) ? (-1.0f) : 1.0f;
	if (counter < 14)
	{
		Vector pos(cOgPos.x, cOgPos.y);
		place = ParabolaPosition(pos, Vector(cHighPoint.x, cHighPoint.y), cUnit, pos.x, counter);
	}
	else
	{
		if (counter == 15)
		{
			character->sprite->orderLayer = characterTarget.y;
			character->stand->orderLayer = characterTarget.y;
			int height = gameState.battle.ground->map[characterTarget.y][characterTarget.x].height;
			character->sprite->setDepth(height * BATTLE_DEPTH_UNIT + 8);
			character->stand->setDepth(height * BATTLE_DEPTH_UNIT + 7);
		}
		place = ParabolaPosition(Vector(cNewPos.x, cNewPos.y), Vector(cHighPoint.x, cHighPoint.y),
												cUnit, cOgPos.x, counter);
	}
	return (place);
}

Vector Rotate::GetTargetWithIterator()
{
	Vector place(0, 0);
	float sign = (MovingLeft(target->position, targetTarget)) ? (-1.0f) : 1.0f;
	if (counter < 14)
	{
		Vector pos(tOgPos.x, tOgPos.y);
		place = ParabolaPosition(pos, Vector(tHighPoint.x, tHighPoint.y), tUnit, pos.x, counter);
	}
	else
	{
		if (counter == 15)
		{
			target->sprite->orderLayer = targetTarget.y;
			target->stand->orderLayer = targetTarget.y;
			int height = gameState.battle.ground->map[targetTarget.y][targetTarget.x].height;
			target->sprite->setDepth(height * BATTLE_DEPTH_UNIT + 8);
			target->stand->setDepth(height * BATTLE_DEPTH_UNIT + 7);
		}
		place = ParabolaPosition(Vector(tNewPos.x, tNewPos.y), Vector(tHighPoint.x, tHighPoint.y),
												tUnit, tOgPos.x, counter);
	}
	return (place);
}

void Rotate::ManageIterator()
{
	if (counter >= 28)
	{
		gameState.modes.disableBars = false;
		done = true;
		gameState.battle.ground->PlaceCharacter(characterTarget, character);
		gameState.battle.ground->PlaceCharacter(targetTarget, target);
	}
	counter++;
}


void Rotate::Update()
{
	if (done)
		return ;
	Vector cPlace = GetCharacterWithIterator();
	Vector tPlcae = GetTargetWithIterator();
	character->Position(cPlace);
	target->Position(tPlcae);
	ManageIterator();
}

void Rotate::Destroy()
{
	gameState.modes.disableBars = false;
	return ;
}
