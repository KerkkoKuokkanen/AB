
#include "../../hdr/global.h"
#define MAX_TIME 30
#define PART_DISTANCE 26000

SupplyEffect::SupplyEffect(Character *target)
{
	if (target->killed)
	{
		done = true;
		return ;
	}
	sur = getSurface(target);
	if (sur == NULL)
	{
		done = true;
		return ;
	}
	PlaySound(gameState.audio.supply, Channels::SUPPLY, 0);
	target->setAnimationActive(true);
	SupplyEffect::target = target;
	counter = 0;
	partCounter = PART_DISTANCE;
	done = false;
	gameState.updateObjs.info->AddSupplyEffect(this);
}

void SupplyEffect::UpdateColor()
{
	if (counter <= 9)
	{
		float gUnit = 136.0f / 9.0f;
		float bUnit = 255.0f / 9.0f;
		int g = 255 - (rounding(gUnit * (float)counter));
		int b = 255 - (rounding(bUnit * (float)counter));
		if (b < 0)
			b = 0;
		target->sprite->ColorMod(255, g, b);
		return ;
	}
	if (counter <= 18)
		return ;
	int count = counter - 18;
	float gUnit = 136.0f / 12.0f;
	float bUnit = 255.0f / 12.0f;
	int g = 119 + rounding(gUnit * (float)count);
	int b = rounding(bUnit * (float)count);
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	target->sprite->ColorMod(255, g, b);
}

void SupplyEffect::CreateParticles(int y, int yTarg)
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
				Vector dir(0.0f, -1.0f);
				float angle = (rand() % 2 == 0) ? (PI / 12.0f) : -(PI / 12.0f);
				vectorRotate(dir, angle);
				float speed = float_rand() * 30.0f + 150.0f;
				Color used(255, 255, 255);
				int life = rand() % 10 + 25;
				float add = float_rand() * 0.02f;
				float drag = 1.03f + float_rand() * 0.2f;
				t_Particle ret = gameState.updateObjs.partManager->ReturnModPartWithText(gameState.textures.supplySymbol, dir, Vector(xP - 500.0f, yP), speed,
																							used, used, life, drag, false, add, {0, 0, 1000, 1000});
				ret.part->Deactivate();
				parts.push_back(ret);
				partCounter = 0;
			}
		}
		y++;
	}
}

void SupplyEffect::ManageParticles()
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

void SupplyEffect::Update()
{
	if (target->killed || done)
	{
		done = true;
		return ;
	}
	UpdateColor();
	ManageParticles();
	counter++;
	if (counter >= MAX_TIME)
		done = true;
}

void SupplyEffect::Destroy()
{
	target->setAnimationActive(false);
	target->sprite->ClearColorMod();
	parts.clear();
}
