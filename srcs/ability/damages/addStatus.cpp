
#include "../../../hdr/global.h"
#define MOVE_TIME 23.0f
#define MOVE_START_TIME 20

void AddStatutsToTarget(Character *target, Character *character, int statusSign, int amount)
{
	if (amount <= 0)
		return ;
	switch (statusSign)
	{
		case StatusSigns::BURN:
		{
			for (int i = 0; i < amount; i++)
			{
				int burnTurns = 3;
				target->statuses.burns.push_back(burnTurns);
			}
			break ;
		}
	}
}

void AddStatus::CreateSprite()
{
	SDL_Rect dest = {0, 0, 2600, 2600};
	switch (statusSign)
	{
		case StatusSigns::BURN:
			status = new Sprite(gameState.textures.statuses.burns[0], dest, NULL, NULL, 0, FLIP_NONE);
			break ;
	}
	gameState.render->AddSprite(status, MISS_LAYER);
	status->orderLayer = 0;
}

void AddStatus::CreateNumber()
{
	if (amount <= 1)
		return ;
	number = new Number(amount, 600, MISS_LAYER, 1, false, NumberType::NORMAL);
	number->ColorMod(168, 168, 168);
}

void AddStatus::PositionStatus(Character *character, Character *target)
{
	Vector place = GetCharacterTopMid(target);
	place.y -= 500.0f;
	if (character->sprite->dest.x > target->sprite->dest.x)
		place.x -= 4500.0f;
	else
		place.x += 2500.0f;
	status->Position(place);
}

void AddStatus::PositionNumber()
{
	if (amount <= 1)
		return ;
	SDL_Rect dest = status->dest;
	int w = number->getFullWidth();
	float x = (float)(dest.x - (w / 2));
	number->Position(Vector(x + 450.0f, (float)(dest.y + 600)));
}

void AddStatus::GetGoal(Character *target)
{
	SDL_Rect dest = target->sprite->dest;
	int dim = status->dest.w / 2;
	int x = dest.x + dest.w / 2;
	int y = dest.y + dest.h / 2;
	goal = {x - dim, y - dim};
}

AddStatus::AddStatus(Character *character, Character *target, int statusSign, int amount)
{
	if (target->killed || amount <= 0)
	{
		done = true;
		return ;
	}
	AddStatus::statusSign = statusSign;
	AddStatus::amount = amount;
	AddStatus::target = target;
	AddStatus::character = character;
	CreateSprite();
	CreateNumber();
	PositionStatus(character, target);
	PositionNumber();
	GetGoal(target);
	Vector dir((float)(goal.x - status->dest.x), (float)(goal.y - status->dest.y));
	dist = dir.Magnitude();
	dir = dir.Normalized();
	direction = {dir.x, dir.y};
}

void AddStatus::MoveEffect()
{
	if (counter < MOVE_START_TIME)
		return ;
	float unit = dist / MOVE_TIME;
	status->Move(Vector(direction.x * unit, direction.y * unit));
}

void AddStatus::ScaleSprite()
{
	if (counter < MOVE_START_TIME)
		return ;
	float amount = (float)status->dest.w - ((float)status->dest.w / 1.15f);
	status->dest.w -= amount;
	status->dest.h -= amount;
}

bool AddStatus::atTarget()
{
	if (Vector((float)(goal.x - status->dest.x), (float)(goal.y - status->dest.y)).Magnitude() < 300.0f)
		return (true);
	return (false);
}

void AddStatus::Update()
{
	if (done)
		return ;
	if (counter == MOVE_START_TIME)
	{
		if (number != NULL)
			delete number;
		number = NULL;
	}
	MoveEffect();
	ScaleSprite();
	if (counter > 80 || atTarget() || target == NULL || target->killed)
	{
		AddStatutsToTarget(target, character, statusSign, amount);
		done = true;
	}
	counter++;
}

void AddStatus::Destroy()
{
	if (number != NULL)
		delete number;
	if (status != NULL)
		delete status;
}
