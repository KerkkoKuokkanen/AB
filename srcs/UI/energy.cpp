
#include "../../hdr/global.h"

#define PART_DIST 200

Energy::Energy()
{
	SDL_Rect dest = {0, 0, 2600, 4100};
	stand = new Sprite(gameState.textures.energy[0], dest, NULL, NULL, 0, FLIP_NONE, true);
	energy = new Sprite(gameState.textures.energy[1], dest, NULL, NULL, 0, FLIP_NONE, true);
	stand->orderLayer = 5;
	energy->orderLayer = 6;
	stand->Deactivate();
	energy->Deactivate();
	energy->ColorMod(190, 190, 190);
	gameState.render->AddSprite(stand, TURN_ORDER_LAYER);
	gameState.render->AddSprite(energy, TURN_ORDER_LAYER);
	sur = gameState.surfaces.energy[1];
}

static Vector getDir()
{
	float angle = float_rand() * (PI / 4.0f);
	Vector ret(0.0f, -1.0f);
	vectorRotate(ret, angle);
	return (ret);
}

static float getSpeed()
{
	float speed = (float)(rand() % 50) + 40.0f;
	return (speed);
}

void Energy::Used(bool particles)
{
	energy->Deactivate();
	if (!particles)
		return ;
	float wUnit = (float)energy->dest.w / (float)sur->w;
	float hUnit = (float)energy->dest.h / (float)sur->h;
	int counter = PART_DIST;
	Uint32 *pixels = (Uint32*)sur->pixels;
	SDL_Rect dest = energy->dest;
	Color start(176, 61, 12);
	for (int y = 0; y < sur->h; y++)
	{
		for (int x = 0; x < sur->w; x++)
		{
			if (pixels[(y * sur->w) + x] == 0)
				continue ;
			counter++;
			if (counter >= PART_DIST)
			{
				float xP = (float)dest.x + (wUnit * (float)x);
				float yP = (float)dest.y + (hUnit * (float)y);
				gameState.updateObjs.partManager->CreateModParticle(getDir(), Vector(xP, yP),
								getSpeed(), start, start, rand() % 30 + 10, 1.015f, true);
				counter = 0;
			}
		}
	}
}

void Energy::TakeBack()
{
	energy->Activate();
}

void Energy::Position(Vector place)
{
	stand->Position(place);
	energy->Position(place);
}

void Energy::Activate()
{
	stand->Activate();
	energy->Activate();
}

void Energy::Deactivate()
{
	stand->Deactivate();
	energy->Deactivate();
}

void Energy::Destroy()
{
	delete stand;
	delete energy;
}
