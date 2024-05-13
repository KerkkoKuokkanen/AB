
#include "../../../hdr/ow/tools/owSpriteMover.h"

OwSpriteMover::OwSpriteMover(Sprite *sprite, SDL_Point start, SDL_Point end, int time)
{
	counter = time;
	OwSpriteMover::sprite = sprite;
	goal = end;
	float xDir = (float)(end.x - start.x);
	float yDir = (float)(end.y - start.y);
	direction = {xDir, yDir};
	direction.x /= (float)time;
	direction.y /= (float)time;
}

void OwSpriteMover::Update()
{
	if (done)
		return ;
	sprite->Move(Vector(direction.x, direction.y));
	counter--;
	if (counter <= 0)
	{
		sprite->dest.x = goal.x;
		sprite->dest.y = goal.y;
		done = true;
	}
}
