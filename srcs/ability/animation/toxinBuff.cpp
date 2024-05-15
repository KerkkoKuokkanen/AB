
#include "../../../hdr/global.h"
#define TOXIN_BUFF_TIME 35
#define PART_DISTANCE 30000

ToxinBuff::ToxinBuff(Character *character)
{
	sur = getSurface(character);
	ToxinBuff::character = character;
	character->setAnimationActive(true);
	partCounter = 29000;
}

void ToxinBuff::ToxinBuffColorChange()
{
	if (counter > 31)
	{
		character->sprite->ClearColorMod();
		return ;
	}
	if (counter <= 20)
	{
		float r = 255.0f / 20.0f;
		float g = (255.0f - 150.0f) / 20.0f;
		float b = (255.0f - 40.0f) / 20.0f;
		int ur = rounding(r * (float)counter);
		int ug = rounding(g * (float)counter);
		int ub = rounding(b * (float)counter);
		int thisr = ((255 - ur) < 1) ? 1 : (255 - ur);
		character->sprite->ColorMod(thisr, 255 - ug, 255 - ub);
		return ;
	}
	int count = counter - 20;
	float r = 255.0f / 11.0f;
	float g = (255.0f - 150.0f) / 11.0f;
	float b = (255.0f - 40.0f) / 11.0f;
	int ur = rounding(r * (float)count);
	int ug = rounding(g * (float)count);
	int ub = rounding(b * (float)count);
	character->sprite->ColorMod(ur, 150 + ug, 40 + ub);
}

void ToxinBuff::CreateParticles(int y, int yTarg)
{
	if (sur == NULL)
		return ;
	float wUnit = (float)character->sprite->dest.w / (float)sur->w;
	float hUnit = (float)character->sprite->dest.h / (float)sur->h;
	Uint32 *pixels = (Uint32*)sur->pixels;
	SDL_Rect dest = character->sprite->dest;
	Color used(255, 255, 255);
	while (y < yTarg && y < sur->h)
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
				Vector dir(0.0f, -1.0f);
				float angle = (rand() % 2 == 0) ? (PI / 12.0f) : -(PI / 12.0f);
				vectorRotate(dir, angle);
				float speed = float_rand() * 30.0f + 200.0f;
				int life = rand() % 20 + 20;
				float add = float_rand() * 0.02f;
				float drag = 1.03f + float_rand() * 0.2f;
				t_Particle ret = gameState.updateObjs.partManager->ReturnModPartWithText(gameState.textures.toxinSymbol, dir, Vector(xP - 500.0f, yP), speed,
																							used, used, life, drag, false, add, {0, 0, 1000, 1000});
				ret.part->Deactivate();
				parts.push_back(ret);
				partCounter = 0;
			}
		}
		y++;
	}
}

void ToxinBuff::Update()
{
	addStatus = false;
	if (done)
		return ;
	if (counter == 5)
		PlaySound(gameState.audio.toxicBlade, Channels::VOLUME_24, 0);
	ToxinBuffColorChange();
	if (counter > 13 && counter < 18)
	{
		int count = counter - 13;
		int h = sur->h / 4;
		int start = h * count;
		int goal = h * (count + 1);
		CreateParticles(start, goal);
	}
	if (counter == 18)
	{
		addStatus = true;
		for (int i = 0; i < parts.size(); i++)
			gameState.updateObjs.partManager->AddModParticle(parts[i]);
		parts.clear();
	}
	counter++;
	if (counter > TOXIN_BUFF_TIME)
		done = true;
}

void ToxinBuff::Destroy()
{
	character->setAnimationActive(false);
	for (int i = 0; i < parts.size(); i++)
	{
		delete parts[i].part->sprite;
		delete parts[i].part;
	}
}
