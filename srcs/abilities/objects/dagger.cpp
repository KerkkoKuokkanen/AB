
#include "../../../hdr/global.h"

SDL_FPoint Dagger::GetTarget(int hitChance, Character *enemy)
{
	int hit = rand() % 101;
	SDL_Rect dest = enemy->sprite->dest;
	SDL_FPoint target = {(float)(dest.x + (dest.w / 2)), (float)(dest.y + (dest.h / 2))};
	if (hit <= hitChance)
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

Dagger::Dagger(Character *start, Character *end, int hitChance)
{
	character = start;
	enemy = end;
	SDL_Rect dest = {start->sprite->dest.x + start->sprite->dest.w / 2 + 600, start->sprite->dest.y + start->sprite->dest.h / 2 - 1600, 1200, 1600};
	sprite = new Sprite(gameState.textures.weaponObjs[DAGGER_OBJ], dest, NULL, NULL, 0, FLIP_NONE);
	target = GetTarget(hitChance, end);
	SDL_FPoint pos = {(float)dest.x + 800.0f, (float)dest.y + 1200.0f};
	Vector dir = Vector(pos.x - target.x, pos.y - target.y).Normalized();
	direction = {dir.x, dir.y};
	float angle = vectorAngle(Vector(0.0f, 1.0f), dir);
	if (pos.x > target.x)
	{
		angle = -angle;
		left = true;
	}
	sprite->setAngle(degree(angle));
	if (pos.y < target.y)
		down = true;
	gameState.render->AddSprite(sprite, OBJECT_LAYER);
}

bool Dagger::TargetMet()
{
	SDL_Point position = {sprite->dest.x + sprite->dest.w / 2, sprite->dest.y + sprite->dest.h / 2};
	SDL_Point targ = {(int)target.x, (int)target.y};
	if (left && down && ((position.x <= target.x && position.y >= target.y) || pointCheck(targ, sprite->dest)))
		return (true);
	if (left && !down && ((position.x <= target.x && position.y <= target.y) || pointCheck(targ, sprite->dest)))
		return (true);
	if (!left && down && ((position.x >= target.x && position.y >= target.y) || pointCheck(targ, sprite->dest)))
		return (true);
	if (!left && !down && ((position.x >= target.x && position.y <= target.y) || pointCheck(targ, sprite->dest)))
		return (true);
	return (false);
}

Vector Dagger::GetDirection()
{
	SDL_Rect cDest = character->sprite->dest;
	SDL_Rect eDest = enemy->sprite->dest;
	Vector toEnemy(cDest.x - eDest.x, cDest.y - eDest.y);
	float angle = vectorAngle(Vector(0.0f, 1.0f), toEnemy);
	float sign = (cDest.x <= eDest.x) ? 1.0f : -1.0f;
	if (angle < PI / 2)
		return(Vector(0.5 * sign, -0.5f));
	return (Vector(0.5f * sign, 0.5f));
}

void Dagger::CreateDamage()
{
	t_Sound add2 = {gameState.audio.daggerThrow[0], DAGGER_THROW0, 0};
	t_Sound add3 = {gameState.audio.daggerThrow[1], DAGGER_THROW1, 0};
	std::vector<t_Sound> sounds = {add2, add3};
	gameState.updateObjs.createDamage->CreateDamage(enemy, Color(255, 0, 0), 5, 5, GetDirection(), sounds);
}

void Dagger::Update()
{
	if (targetFound)
		return;
	if (TargetMet())
	{
		remove = true;
		targetFound = true;
		if (!missing)
		{
			CreateDamage();
			return ;
		}
		SDL_Point pos = {sprite->dest.x + sprite->dest.w / 2, sprite->dest.y + sprite->dest.h / 2};
		CreateDust(pos, Vector(direction.x, direction.y));
	}
	sprite->Move(Vector(-direction.x * speed, -direction.y * speed));
	speed /= 1.02f;
}

void Dagger::Destroy()
{
	delete sprite;
}
