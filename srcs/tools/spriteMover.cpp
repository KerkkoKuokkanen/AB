
#include "../../hdr/global.h"

SpriteMover::SpriteMover(Sprite *sprite, Vector direction, int time, float speed)
{
	if (sprite == NULL)
	{
		SpriteMover::time = 0;
		return ;
	}
	SpriteMover::speed = speed;
	SpriteMover::sprite = sprite;
	direction = direction.Normalized();
	dir = {direction.x, direction.y};
	time = (time % 2 != 0) ? time + 1 : time;
	SpriteMover::time = time;
	half = time / 2;
	counter = 0;
	SDL_Rect dest = sprite->dest;
	startPosition = {dest.x, dest.y};
}

void SpriteMover::MoveSprite()
{
	if (counter < half)
	{
		float x = dir.x * speed;
		float y = dir.y * speed;
		sprite->Move(Vector(x, y));
		return ;
	}
	float x = -dir.x * speed;
	float y = -dir.y * speed;
	sprite->Move(Vector(x, y));
}

int SpriteMover::Update()
{
	if (time <= 0)
		return (-1);
	counter++;
	time--;
	MoveSprite();
	if (time <= 0)
		return (-1);
	return (counter);
}

void SpriteMover::Destroy()
{
	sprite->Position(Vector((float)startPosition.x, (float)startPosition.y));
}
