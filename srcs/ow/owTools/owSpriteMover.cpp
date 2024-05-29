
#include "../../../hdr/ow/tools/owSpriteMover.h"

OwSpriteMover::OwSpriteMover(Sprite *sprite, SDL_Point start, SDL_Point end, int time)
{
	counter = 0;
	goal = end;
	OwSpriteMover::sprite = sprite;
	SDL_FPoint starter = {(float)start.x, (float)start.y};
	Vector magVec((float)(end.x - start.x), (float)(end.y - start.y));
	for (int i = 0; i < time; i++)
	{
		float unit = 1.0f - ((float)i / (float)time);
		float multi = 1.0f - (unit * unit * unit);
		SDL_FPoint pos = starter;
		pos.x += magVec.x * multi;
		pos.y += magVec.y * multi;
		SDL_Point add = {(int)pos.x, (int)pos.y};
		travelPoints.push_back(add);
	}
	travelPoints.push_back(end);
}

void OwSpriteMover::Update()
{
	if (done)
		return ;
	if (counter >= travelPoints.size())
	{
		done = true;
		sprite->dest.x = goal.x;
		sprite->dest.y = goal.y;
		return ;
	}
	SDL_Point pos = travelPoints[counter];
	sprite->dest.x = pos.x;
	sprite->dest.y = pos.y;
	counter++;
}
