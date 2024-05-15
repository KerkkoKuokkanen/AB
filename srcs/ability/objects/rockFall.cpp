
#include "../../../hdr/global.h"

static Color getColor()
{
	int hit = rand() % 100;
	if (hit > 90)
		return (Color(64, 57, 48));
	if (hit > 70)
		return (Color(1, 1, 1));
	if (hit > 50)
		return (Color(166, 134, 94));
	return (Color(97, 70, 36));
}

static float getSpeed(Vector dir)
{
	float angle = (dir.x < 0.0f) ? vectorAngle(Vector(-1.0f, 0.0f), dir) : vectorAngle(Vector(1.0f, 0.0f), dir);
	float unit = 1000.0f / (PI * 0.5f);
	float speed = 1000.0f - (unit * angle);
	return (speed + 300.0f);
}

RockFall::RockFall(SDL_Point target)
{
	PlaySound(gameState.audio.meteors[0], Channels::METEOR1, 0);
	RockFall::target = target;
	SDL_Rect dest = gameState.battle.ground->getTileDest(target);
	SDL_Rect used = {dest.x - 3300, dest.y - 12160, 4800, 4800};
	sprite = new Sprite(gameState.textures.attacks.rockFall, used, NULL, NULL, 0, FLIP_NONE);
	sprite->setDepth(gameState.battle.ground->map[target.y][target.x].height * BATTLE_DEPTH_UNIT + 9);
	sprite->orderLayer = target.y;
	gameState.render->AddSprite(sprite, BATTLEGROUND_LAYER);
	sprite->AlphaMod(0);
}

void RockFall::UpdateAlpha()
{
	if (counter > 15)
	{
		sprite->ClearAlphaMod();
		return ;
	}
	float unit = 255.0f / 15.0f;
	float alpha = unit * (float)counter;
	int used = rounding(alpha);
	if (used < 0)
		used = 0;
	if (used > 255)
		used = 255;
	sprite->AlphaMod(used);
}

void RockFall::MoveRocks()
{
	if (counter > 40)
		return ;
	SDL_Rect dest = sprite->dest;
	dest.x += 90;
	dest.y += 262;
	sprite->dest = dest;
}

void RockFall::CreateParticles()
{
	SDL_Point place = {sprite->dest.x + 2400, sprite->dest.y + 3500};
	for (int i = 0; i < 140; i++)
	{
		int xAdd = rand() % 200 - rand() % 200;
		Vector dir(0.0f, -1.0f);
		float angle = float_rand() * PI;
		angle = (rand() % 2 == 0) ? angle : -angle;
		vectorRotate(dir, angle);
		float speed = getSpeed(dir);
		Color used = getColor();
		int life = rand() % 10 + 25;
		float drag = 1.01f + float_rand() * 0.3f;
		gameState.updateObjs.partManager->CreateModParticle(dir, Vector((float)place.x + xAdd, (float)place.y), speed, used,
																						used, life, drag, false);
	}
}

void RockFall::UpdateFadeAlpha()
{
	if (counter < 60)
		return ;
	int count = counter - 60;
	float unit = 255.0f / 15.0f;
	float alpha = 255.0f - (unit * (float)count);
	int used = rounding(alpha);
	if (used < 0)
		used = 0;
	if (used > 255)
		used = 255;
	sprite->AlphaMod(used);
}

void RockFall::Update()
{
	createDamage = false;
	if (done)
		return ;
	UpdateAlpha();
	MoveRocks();
	UpdateFadeAlpha();
	if (counter == 38)
	{
		PlaySound(gameState.audio.meteors[1], Channels::METEOR2, 0);
		PlaySound(gameState.audio.meteors[2], Channels::METEOR3, 0);
		SetScreenShake(700, 8);
		CreateParticles();
		createDamage = true;
	}
	counter++;
	if (counter > 75)
		done = true;
}

void RockFall::Destroy()
{
	if (sprite != NULL)
		delete sprite;
}
