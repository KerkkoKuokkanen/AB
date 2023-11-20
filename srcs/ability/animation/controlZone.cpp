
#include "../../../hdr/global.h"
#define TIME 30
#define PART_DISTANCE 26000

ControlZone::ControlZone(Character *character)
{
	PlaySound(gameState.audio.BuffEffect, Channels::BUFF_EFFECT, 0);
	ControlZone::character = character;
	character->setAnimationActive(true);
	sur = getSurface(character);
	counter = 0;
	partCounter = rand() % PART_DISTANCE;
}

void ControlZone::UpdateColor()
{
	float unit = 255.0f / 10.0f;
	if (counter <= 10)
	{
		float col = 255.0f - (unit * (float)counter);
		int used = rounding(col);
		if (used < 0)
			used = 1;
		character->sprite->ColorMod(used, 255, used);
		return ;
	}
	if (counter >= 20)
	{
		int count = counter - 20;
		float col = unit * (float)count;
		int used = rounding(col);
		if (used < 0)
			used = 1;
		if (used > 255)
			used = 255;
			character->sprite->ColorMod(used, 255, used);
	}
}

void ControlZone::CreateParticles(int start, int goal)
{
	if (sur == NULL)
		return ;
	float wUnit = (float)character->sprite->dest.w / (float)sur->w;
	float hUnit = (float)character->sprite->dest.h / (float)sur->h;
	Uint32 *pixels = (Uint32*)sur->pixels;
	SDL_Rect dest = character->sprite->dest;
	int y = start;
	while (y < goal && y < sur->h)
	{
		for (int x = 0; x < sur->w; x++)
		{
			if (pixels[(y * sur->w) + x] == 0)
				continue ;
			partCounter++;
			if (partCounter >= PART_DISTANCE)
			{
				float xP = (float)dest.x + (wUnit * (float)x);
				float yP = (float)dest.y + (hUnit * (float)y);
				Vector dir = Vector(0.0f, -1.0f);
				float angle = (rand() % 2 == 0) ? (PI / 12.0f) : -(PI / 12.0f);
				vectorRotate(dir, angle);
				float speed = float_rand() * 30.0f + 150.0f;
				Color used(0, 150, 0);
				int life = rand() % 10 + 25;
				float add = float_rand() * 0.02f;
				float drag = 1.03f + float_rand() * 0.2f;
				t_Particle ret = gameState.updateObjs.partManager->ReturnModPartWithText(gameState.textures.control, dir, Vector(xP - 500.0f, yP), speed,
																							used, used, life, drag, false, add, {0, 0, 1000, 1000});
				ret.part->Deactivate();
				parts.push_back(ret);
				partCounter = 0;
			}
		}
		y++;
	}
}

void ControlZone::ManageParticles()
{
	if (counter == 12)
	{
		for (int i = 0; i < parts.size(); i++)
			gameState.updateObjs.partManager->AddModParticle(parts[i]);
		return ;
	}
	if (counter < 8 || counter > 11)
		return ;
	int count = counter - 8;
	int h = sur->h / 4;
	int start = h * count;
	int goal = h * (count + 1);
	CreateParticles(start, goal);
}

void ControlZone::Update()
{
	createBuff = false;
	if (done)
		return ;
	counter++;
	UpdateColor();
	ManageParticles();
	if (counter == 12)
		createBuff = true;
	if (counter >= TIME)
		done = true;
}

void ControlZone::Destroy()
{
	parts.clear();
	character->sprite->ClearColorMod();
	character->setAnimationActive(false);
}
