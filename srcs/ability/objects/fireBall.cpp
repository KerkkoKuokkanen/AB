
#include "../../../hdr/global.h"
#define MISSING_MINIMUM_DIST 3000.0f
#define FIRE_BALL_SPEED 350.0f

void FireBall::GetMissingGoal(SDL_Point target)
{
	SDL_Rect dest = gameState.battle.ground->map[target.y][target.x].character->sprite->dest;
	SDL_Point mid = {dest.x + (dest.w / 2), dest.y + (dest.h / 2)};
	SDL_Rect cDest = character->sprite->dest;
	SDL_Point cMid = {cDest.x + (cDest.w / 2), cDest.y + (cDest.h / 2)};
	float basicMagnitude = Vector((float)(mid.x - cMid.x), (float)(mid.y - cMid.y)).Magnitude();
	float angle = float_rand() * (PI * 2.0f);
	float dist = (float)(rand() % 6000) + MISSING_MINIMUM_DIST;
	Vector dir(0.0f, 1.0f);
	vectorRotate(dir, angle);
	dir.x *= dist;
	dir.y *= dist;
	dir.x = (rand() % 2 == 0) ? dir.x : (dir.x * (-1.0f));
	dir.y = (rand() % 2 == 0) ? dir.y : (dir.y * (-1.0f));
	goal = {mid.x + (int)dir.x, mid.y + (int)dir.y};
	while (Vector((float)(goal.x - cMid.x), (float)(goal.y - cMid.y)).Magnitude() < basicMagnitude ||
		Vector((float)(goal.x - cMid.x), (float)(goal.y - cMid.y)).Magnitude() < 3000.0f)
	{
		float angle = float_rand() * (PI * 2.0f);
		float dist = (float)(rand() % 6000) + MISSING_MINIMUM_DIST;
		Vector dir(0.0f, 1.0f);
		vectorRotate(dir, angle);
		dir.x *= dist;
		dir.y *= dist;
		dir.x = (rand() % 2 == 0) ? dir.x : (dir.x * (-1.0f));
		dir.y = (rand() % 2 == 0) ? dir.y : (dir.y * (-1.0f));
		goal = {mid.x + (int)dir.x, mid.y + (int)dir.y};
	}
}

void FireBall::GetGoal(SDL_Point target, bool missing)
{
	if (missing)
	{
		GetMissingGoal(target);
		return ;
	}
	SDL_Rect dest = gameState.battle.ground->map[target.y][target.x].character->sprite->dest;
	goal = {dest.x + (dest.w / 2), dest.y + (dest.h / 2)};
}

FireBall::FireBall(Character *character, SDL_Point target, bool goingToMiss)
{
	FireBall::character = character;
	GetGoal(target, goingToMiss);
	SDL_Rect cDest = character->sprite->dest;
	SDL_Rect dest = {cDest.x + 4800, cDest.y + 1500, 2400, 2400};
	sprite = new Sprite(gameState.textures.attacks.fireBall[0], dest, NULL, NULL, 0, FLIP_NONE);
	gameState.render->AddSprite(sprite, OBJECT_LAYER);
	direction = {1.0f, 0.0f};
	float angle = vectorAngle(Vector(0.0f, 1.0f), Vector(1.0f, 0.0f));
	sprite->setAngle(degree(angle));
	missing = goingToMiss;
}

void FireBall::RotateDirection()
{
	SDL_Point place = {sprite->dest.x + (sprite->dest.w / 2), sprite->dest.y + (sprite->dest.h / 2)};
	Vector dir((float)(goal.x - place.x), (float)(goal.y - place.y));
	dir = dir.Normalized();
	Vector currDir(direction.x, direction.y);
	currDir.x = currDir.x + (dir.x * 0.5f);
	currDir.y = currDir.y + (dir.y * 0.5f);
	currDir = currDir.Normalized();
	direction.x = currDir.x;
	direction.y = currDir.y;
}

void FireBall::MoveFireBall()
{
	sprite->Move(Vector(direction.x * FIRE_BALL_SPEED, direction.y * FIRE_BALL_SPEED));
	float angle = vectorAngle(Vector(0.0f, 1.0f), Vector(direction.x, direction.y));
	angle -= PI;
	if (direction.x > 0.0f)
		angle *= (-1.0f);
	sprite->setAngle(degree(angle));
}

bool FireBall::AtTarget()
{
	SDL_Point place = {sprite->dest.x + (sprite->dest.w / 2), sprite->dest.y + (sprite->dest.h / 2)};
	Vector dir((float)(goal.x - place.x), (float)(goal.y - place.y));
	float dist = dir.Magnitude();
	if (dist < 1000.0f)
		return (true);
	return (false);
}

void FireBall::ChangeTexture()
{
	if (counter % 8 == 0 && counter != 0)
	{
		if (firstText)
		{
			firstText = false;
			sprite->setTexture(gameState.textures.attacks.fireBall[1]);
		}
		else
		{
			firstText = true;
			sprite->setTexture(gameState.textures.attacks.fireBall[0]);
		}
	}
}

Color FireBall::getColor()
{
	int hit = rand() % 100;
	if (hit > 90)
		return (Color(1, 1, 1));
	if (hit < 55)
		return (Color(255, 24, 0));
	return (Color(209, 110, 0));
}

void FireBall::TurnToParticles()
{
	SDL_Rect dest = sprite->dest;
	Vector mid((float)(dest.x + dest.w / 2), (float)(dest.y + dest.h / 2));
	for (int i = 0; i < 250; i++)
	{
		float angle = float_rand() * (2.0f * PI);
		Vector dir(0.0f, 1.0f);
		vectorRotate(dir, angle);
		int life = rand() % 20 + 20;
		float drag = 1.0f + float_rand() * 0.1f;
		float speed = float_rand() * 70.0f + 80.0f;
		float x = float_rand() - float_rand() * 800.0f;
		float y = float_rand() - float_rand() * 800.0f;
		Color used = getColor();
		gameState.updateObjs.partManager->CreateModParticle(dir, Vector(mid.x + x, mid.y + y), speed, used, used, life, drag, false);
	}
}

void FireBall::Update()
{
	if (destroy)
		return ;
	ChangeTexture();
	RotateDirection();
	MoveFireBall();
	if (AtTarget() || counter > 180)
	{
		PlaySound(gameState.audio.flameBlast[0], Channels::FLAME_BLAST_EXPLOSION, 0);
		TurnToParticles();
		destroy = true;
		return ;
	}
	counter++;
}

void FireBall::Destroy()
{
	delete sprite;
}
