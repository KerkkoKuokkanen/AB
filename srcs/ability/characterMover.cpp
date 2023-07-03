
#include "../../hdr/global.h"

CharacterMover::CharacterMover(Character *character, Vector direction, int firstTime, int secondTime, float speed, bool linear)
{
	totalTime = firstTime + secondTime;
	CharacterMover::firstTime = firstTime;
	Vector ddir = direction.Normalized();
	dir = {ddir.x, ddir.y};
	CharacterMover::character = character;
	linearAlgo = linear;
	ogPos = character->sprite->dest;
	totalCopy = totalTime;
	CharacterMover::speed = speed;
}

void CharacterMover::LinearMover()
{
	if (counter < firstTime)
	{
		int duration = firstTime;
		float speed = (100.0f / ((float)(totalCopy - duration + 1))) + 80.0f;
		character->sprite->Move(Vector(dir.x * speed, dir.y * speed));
		return ;
	}
	int time = totalCopy;
	float speed = (100.0f / (float)time) + 80.0f;
	character->sprite->Move(Vector(-dir.x * speed, -dir.y * speed));
}

void CharacterMover::SmoothMover()
{
	if (counter < firstTime)
	{
		float amount = 250.0f / ((float)counter + 1.0f);
		character->sprite->Move(Vector(dir.x * amount, dir.y * amount));
		return ;
	}
	float divider = (firstTime + 1.0f - (counter - firstTime));
	if (divider == 0)
		divider = 1.0f;
	float amount = 250.0f / divider;
	character->sprite->Move(Vector(-dir.x * amount, -dir.y * amount));
}

int CharacterMover::Update()
{
	if (counter >= totalTime)
	{
		if (!positioned)
		{
			positioned = true;
			character->sprite->Position(Vector((float)ogPos.x, (float)ogPos.y));
		}
		return (ANIMATION_DONE);
	}
	if (linearAlgo)
		LinearMover();
	else
		SmoothMover();
	totalCopy--;
	counter++;
	return (counter);
}
