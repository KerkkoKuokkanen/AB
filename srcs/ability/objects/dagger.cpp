
#include "../../../hdr/global.h"

SDL_FPoint Dagger::GetTarget(bool goingToHit, Character *enemy)
{
	int hit = rand() % 100;
	SDL_Rect dest = enemy->sprite->dest;
	SDL_FPoint target = {(float)(dest.x + (dest.w / 2)), (float)(dest.y + (dest.h / 2))};
	if (goingToHit)
		return (target);
	missing = true;
	int xRand = rand() % 3500 + 1000;
	int yRand = rand() % 3500 + 1000;
	float xSign = (rand() % 2 == 0) ? 1.0f : (-1.0f);
	float ySign = (rand() % 2 == 0) ? 1.0f : (-1.0f);
	target.x += xRand * xSign;
	target.y += yRand * ySign;
	return (target);
}

Dagger::Dagger(Character *start, Character *end, bool gointToHit)
{
	character = start;
	enemy = end;
	SDL_Rect dest = {start->sprite->dest.x + start->sprite->dest.w / 2 + 600, start->sprite->dest.y + start->sprite->dest.h / 2 - 1600, 1300, 1600};
	sprite = new Sprite(gameState.textures.weaponObjs[DAGGER_OBJ], dest, NULL, NULL, 0, FLIP_NONE);
	target = GetTarget(gointToHit, end);
	SDL_FPoint pos = {(float)dest.x + 650.0f, (float)dest.y + 800.0f};
	Vector dir = Vector(pos.x - target.x, pos.y - target.y).Normalized();
	direction = {dir.x, dir.y};
	float angle = vectorAngle(Vector(0.0f, 1.0f), dir);
	if (pos.x > target.x)
		angle = -angle;
	sprite->setAngle(degree(angle));
	gameState.render->AddSprite(sprite, OBJECT_LAYER);
}

bool Dagger::TargetMet()
{
	SDL_Point position = {sprite->dest.x + sprite->dest.w / 2, sprite->dest.y + sprite->dest.h / 2};
	SDL_Point targ = {(int)target.x, (int)target.y};
	float mag = Vector((float)position.x - (float)targ.x, (float)position.y - (float)targ.y).Magnitude();
	if (mag < 1000.0f)
		return (true);
	return (false);
}

void Dagger::CreateParticles()
{
	int iter = 2;
	Vector place((float)(sprite->dest.x + sprite->dest.w / 2), (float)(sprite->dest.y + sprite->dest.h / 2));
	place.x += direction.x * 400.0f;
	place.y += direction.y * 400.0f;
	for (int i = 0; i < iter; i++)
	{
		int lifeTime = rand() % 10 + 20;
		float angle = float_rand() * (PI / 8.0f);
		angle = (rand() % 2 == 0) ? angle : -angle;
		float speed = (float)(rand() % 80 + 90);
		Vector dir(direction.x, direction.y);
		vectorRotate(dir, angle);
		gameState.updateObjs.partManager->CreateModParticle(dir, place, speed, Color(200, 200, 200), Color(200, 200, 200), lifeTime, 1.1, false);
	}
}

void Dagger::Update()
{
	if (targetFound)
		return;
	if (TargetMet() || destroyCounter <= 0)
	{
		remove = true;
		targetFound = true;
		if (!missing)
		{
			createDamage = true;
			return ;
		}
		SDL_Point pos = {sprite->dest.x + sprite->dest.w / 2, sprite->dest.y + sprite->dest.h / 2};
		PlaySound(gameState.audio.whiff, Channels::WHIFF, 0);
		CreateDust(pos, Vector(direction.x, direction.y));
	}
	CreateParticles();
	sprite->Move(Vector(-direction.x * speed, -direction.y * speed));
	speed /= 1.02f;
	destroyCounter--;
}

void Dagger::Destroy()
{
	delete sprite;
}
