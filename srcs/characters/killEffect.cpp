
#include "../../hdr/global.h"
#define PART_DISTANCE 500
# define KILL_TIME 50

KillEffect::KillEffect(SDL_Surface *sur, Sprite *character, Sprite *stand)
{
	PlaySound(gameState.audio.kills[2], Channels::VOLUME_4, 0);
	SDL_Rect dest = character->dest;
	int order = character->orderLayer;
	float z = character->z;
	KillEffect::sur = sur;
	sRect = {0, 0, 0, 0};
	sRect.w = sur->w;
	sRect.h = sur->h;
	KillEffect::character = new Sprite(character->getTexture(), dest, &sRect, NULL, 0, character->flipSign);
	KillEffect::stand = new Sprite(stand->getTexture(), dest, NULL, NULL, 0, character->flipSign);
	KillEffect::character->z = z;
	KillEffect::character->orderLayer = order;
	KillEffect::stand->z = z - 0.1f;
	KillEffect::stand->orderLayer = order;
	KillEffect::character->ColorMod(2, 2, 2);
	gameState.render->AddSprite(KillEffect::character, BATTLEGROUND_LAYER);
	gameState.render->AddSprite(KillEffect::stand, BATTLEGROUND_LAYER);
	iterAmount = sRect.h / KILL_TIME;
	counter = KILL_TIME;
	partCounter = PART_DISTANCE;
	int h = character->dest.h;
	float unit = (float)h / (float)sur->h;
	heightAmount = rounding(unit * (float)iterAmount);
}

void KillEffect::ManageSrect()
{
	character->dest.h -= heightAmount;
	character->dest.y += heightAmount;
	sRect.y += iterAmount;
}

void KillEffect::ManageParticles(int start, int end)
{
	if (end >= sur->h)
		return ;
	float wUnit = (float)character->dest.w / (float)sur->w;
	float hUnit = (float)character->dest.h / (float)sur->h;
	Uint32 *pixels = (Uint32*)sur->pixels;
	SDL_Rect dest = character->dest;
	int y = start;
	while (y < end)
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
				float angle = float_rand() * (PI);
				angle = (rand() % 2 == 0) ? -angle : angle;
				vectorRotate(dir, angle);
				float speed = rand() % 150 + 50;
				int life = rand() % 30 + 25;
				gameState.updateObjs.partManager->CreateModParticle(dir, Vector(xP, yP), speed,
													Color(2, 2, 2), Color(110, 110, 110), life, 1.02f, false, -0.03f);
				partCounter = 0;
			}
		}
		y++;
	}
}

void KillEffect::Update()
{
	if (done)
		return ;
	counter--;
	if (counter <= 0)
	{
		done = true;
		return ;
	}
	int start = iterAmount * partCount;
	int end = iterAmount * (partCount + 1);
	ManageParticles(start, end);
	partCount++;
	ManageSrect();
}

void KillEffect::Destroy()
{
	delete character;
	delete stand;
}
