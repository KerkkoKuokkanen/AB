
#include "../../hdr/global.h"
#define ORDER_UNIT 200000

void ThrowArch::CalculateMidPoint()
{
	Vector dir = Vector((float)(end.x - start.x), (float)(end.y - start.y));
	totalMag = dir.Magnitude();
	midMag = Vector(dir.x * 0.5f, dir.y * 0.5f).Magnitude();
	Vector tang = dir.Normalized();
	direction = {tang.x, tang.y};
	if (dir.x > 0.0f)
		vectorRotate(tang, -(PI / 2.0f));
	else
		vectorRotate(tang, (PI / 2.0f));
	midPoint = {rounding(dir.x * 0.5f), rounding(dir.y * 0.5f)};
	midDir = {tang.x, tang.y};
	float angle = vectorAngle(Vector(0.0f, -1.0f), dir);
	if (angle > (PI / 2.0f))
		angle = PI - angle;
	float unit = 1.0f / (PI / 2.0f);
	angleMulti = unit * angle;
}

ThrowArch::ThrowArch(Sprite *sprite, SDL_Point start, SDL_Point end, float maxDist, float speed)
{
	if (sprite == NULL)
	{
		done = true;
		return ;
	}
	ThrowArch::sprite = sprite;
	ThrowArch::start = start;
	ThrowArch::end = end;
	ThrowArch::speed = speed;
	midPoint = {0, 0};
	max = maxDist;
	CalculateMidPoint();
	sprite->Position(Vector((float)start.x, (float)start.y));
	ogOrder = sprite->orderLayer;
	sprite->orderLayer = ORDER_UNIT;
}

SDL_FPoint ThrowArch::GetPosition()
{
	float count = (float)counter;
	SDL_FPoint pos = {speed * count * direction.x, speed * count * direction.y};
	return (pos);
}

SDL_FPoint ThrowArch::MoveUp(SDL_FPoint pos)
{
	SDL_FPoint mid = {(float)midPoint.x, (float)midPoint.y};
	float dist = Vector(mid.x - pos.x, mid.y - pos.y).Magnitude();
	float ogDist = Vector(mid.x, mid.y).Magnitude();
	float multi = fabs(ogDist - dist);
	multi = (2.0f * sqrt(multi) * max) * angleMulti;
	SDL_FPoint ret = {pos.x + (midDir.x * multi), pos.y + (midDir.y * multi)};
	return (ret);
}

void ThrowArch::MoveSprite(SDL_FPoint pos)
{
	SDL_FPoint s = {(float)start.x, (float)start.y};
	float currMag = Vector(s.x + pos.x - s.x, s.y + pos.y - s.y).Magnitude();
	SDL_FPoint ret = MoveUp(pos);
	SDL_Point position = {start.x + (int)ret.x, start.y + (int)ret.y};
	sprite->dest.x = position.x;
	sprite->dest.y = position.y;
}

bool ThrowArch::CheckIfDone(SDL_FPoint pos)
{
	SDL_FPoint s = {(float)start.x, (float)start.y};
	float currMag = Vector(s.x + pos.x - s.x, s.y + pos.y - s.y).Magnitude();
	if (currMag >= totalMag)
		return (true);
	return (false);
}

void ThrowArch::Update()
{
	if (done)
		return ;
	SDL_FPoint ret = GetPosition();
	bool dd = CheckIfDone(ret);
	if (dd)
	{
		sprite->orderLayer = ogOrder;
		sprite->Position(Vector((float)end.x, (float)end.y));
		done = true;
		return ;
	}
	MoveSprite(ret);
	counter++;
	if (counter > 250)
	{
		sprite->orderLayer = ogOrder;
		sprite->Position(Vector((float)end.x, (float)end.y));
		done = true;
	}
}

void ThrowArch::Destroy()
{
	sprite->orderLayer = ogOrder;
	sprite->Position(Vector((float)end.x, (float)end.y));
	return ;
}
