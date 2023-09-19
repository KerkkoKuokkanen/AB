
#include "../../hdr/global.h"
#define TIME 30
#define PART_DISTANCE 26000

BuffEffect::BuffEffect(Character *target, bool buff)
{
	BuffEffect::target = target;
	BuffEffect::buff = buff;
	sur = getSurface(target);
	gameState.updateObjs.info->AddBuffEffect(this);
	partCounter = rand() % PART_DISTANCE;
	if (buff)
		PlaySound(gameState.audio.BuffEffect, Channels::BUFF_EFFECT, 0);
	else
		PlaySound(gameState.audio.deBuffEffect, Channels::BUFF_EFFECT, 0);
}

void BuffEffect::CreateParticles(int y, int yTarg)
{
	if (sur == NULL)
		return ;
	float wUnit = (float)target->sprite->dest.w / (float)sur->w;
	float hUnit = (float)target->sprite->dest.h / (float)sur->h;
	Uint32 *pixels = (Uint32*)sur->pixels;
	SDL_Rect dest = target->sprite->dest;
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
				if (!buff)
					yP -= 1200.0f;
				Vector dir = (buff) ? Vector(0.0f, -1.0f) : Vector(0.0f, 1.0f);
				float angle = (rand() % 2 == 0) ? (PI / 12.0f) : -(PI / 12.0f);
				vectorRotate(dir, angle);
				float speed = float_rand() * 30.0f + 150.0f;
				Color used = (buff) ? Color(23, 96, 255) : Color(255, 60, 22);
				int life = rand() % 10 + 25;
				float add = float_rand() * 0.02f;
				float drag = 1.03f + float_rand() * 0.2f;
				t_Particle ret = gameState.updateObjs.partManager->ReturnModPartWithText(gameState.textures.buffSymbol, dir, Vector(xP - 500.0f, yP), speed,
																							used, used, life, drag, false, add, {0, 0, 1000, 1000});
				ret.part->Deactivate();
				int flip = (buff) ? FLIP_NONE : FLIP_VERTICAL;
				ret.part->sprite->setFlip(flip);
				parts.push_back(ret);
				partCounter = 0;
			}
		}
		y++;
	}
}

void BuffEffect::ManageParticles()
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

void BuffEffect::UpdateDeBuffColor()
{
	if (counter <= 9)
	{
		float gUnit = 195.0f / 9.0f;
		float bUnit = 233.0f / 9.0f;
		int g = 255 - (rounding(gUnit * (float)counter));
		int b = 255 - (rounding(bUnit * (float)counter));
		target->sprite->ColorMod(255, g, b);
		return ;
	}
	if (counter <= 18)
		return ;
	int count = counter - 18;
	float gUnit = 195.0f / 12.0f;
	float bUnit = 233.0f / 12.0f;
	int g = 60 + rounding(gUnit * (float)count);
	int b = 22 + rounding(bUnit * (float)count);
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	target->sprite->ColorMod(255, g, b);
}

void BuffEffect::UpdateDebuff()
{
	UpdateDeBuffColor();
	ManageParticles();
}

void BuffEffect::UpdateBuffColor()
{
	if (counter <= 9)
	{
		float rUnit = 232.0f / 9.0f;
		float gUnit = 159.0f / 9.0f;
		int g = 255 - (rounding(gUnit * (float)counter));
		int r = 255 - (rounding(rUnit * (float)counter));
		target->sprite->ColorMod(r, g, 255);
		return ;
	}
	if (counter <= 18)
		return ;
	int count = counter - 18;
	float rUnit = 232.0f / 12.0f;
	float gUnit = 159.0f / 12.0f;
	int r = 23 + rounding(rUnit * (float)count);
	int g = 96 + rounding(gUnit * (float)count);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	target->sprite->ColorMod(r, g, 255);
}

void BuffEffect::UpdateBuff()
{
	UpdateBuffColor();
	ManageParticles();
}

void BuffEffect::Update()
{
	if (done)
		return ;
	if (buff)
		UpdateBuff();
	else
		UpdateDebuff();
	counter++;
	if (counter > TIME)
		done = true;
}

void BuffEffect::Destroy()
{
	target->sprite->ClearColorMod();
	parts.clear();
}
