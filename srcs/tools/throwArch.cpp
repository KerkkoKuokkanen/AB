
#include "../../hdr/global.h"
#define ORDER_UNIT 200000

void ThrowArch::GetDirection()
{
	Vector dir((float)(end.x - start.x), (float)(end.y - start.y));
	magnitude = dir.Magnitude();
	maxDir = {dir.x, dir.y};
	dir = dir.Normalized();
	direction = {dir.x, dir.y};
	float angle = (dir.x > 0.0f) ? (-PI * 0.5f) : PI * 0.5f;
	vectorRotate(dir, angle);
	dir = dir.Normalized();
	addDir = {dir.x, dir.y};
}

void ThrowArch::GetDirectionMulti()
{
	float angle = fabs(vectorAngle(Vector(0.0f, -1.0f), Vector(direction.x, direction.y)));
	angle = (angle > (PI * 0.5f)) ? PI - angle : angle;
	directionalMulti = angle / (PI * 0.5f);
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
	max = maxDist;
	sprite->Position(Vector((float)start.x, (float)start.y));
	ogOrder = sprite->orderLayer;
	sprite->orderLayer = ORDER_UNIT;
	position = {(float)start.x, (float)start.y};
	GetDirection();
	GetDirectionMulti();
}

void ThrowArch::UpdatePosition()
{
	position.x += direction.x * speed;
	position.y += direction.y * speed;
}

void ThrowArch::PlaceSprite()
{
	Vector currDist((float)end.x - position.x, (float)end.y - position.y);
	float currMag = currDist.Magnitude();
	float x = 1.0f - (currMag / magnitude);
	float multi = -(x * x) + x;
	float xAdd = addDir.x * multi * max * directionalMulti;
	float yAdd = addDir.y * multi * max * directionalMulti;
	SDL_FPoint pos = {position.x + xAdd, position.y + yAdd};
	sprite->Position(Vector(pos.x, pos.y));
}

bool ThrowArch::CheckIfDone()
{
	Vector where((float)end.x - position.x, (float)end.y - position.y);
	if (where.Magnitude() < 500.0f)
		return (true);
	return (false);
}

void ThrowArch::Update()
{
	if (done)
		return ;
	UpdatePosition();
	PlaceSprite();
	counter++;
	if (counter > 500 || CheckIfDone())
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
