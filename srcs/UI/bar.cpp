
#include "../../hdr/global.h"

#define BAR_SOURCE_WIDTH 800.0f

Bar::Bar(SDL_Rect dest)
{
	bar = new Sprite(gameState.textures.bar[0], dest, NULL, NULL, 0, FLIP_NONE, true);
	backGround = new Sprite(gameState.textures.bar[1], dest, NULL, NULL, 0, FLIP_NONE, true);
	filler = new Sprite(gameState.textures.barFiller, dest, &sRect, NULL, 0, FLIP_NONE, true);
	bar->orderLayer = 3;
	backGround->orderLayer = 1;
	filler->orderLayer = 2;
	gameState.render->AddSprite(bar, TURN_ORDER_LAYER);
	gameState.render->AddSprite(backGround, TURN_ORDER_LAYER);
	gameState.render->AddSprite(filler, TURN_ORDER_LAYER);
}

void Bar::Update(int max, int curr, Uint8 r, Uint8 g, Uint8 b)
{
	filler->ColorMod(r, g, b);
	if (max <= curr)
	{
		filler->dest = bar->dest;
		return ;
	}
	float unit = (float)bar->dest.w / (float)max;
	float sUnit = BAR_SOURCE_WIDTH / (float)max;
	sRect.w = rounding(sUnit * (float)curr);
	filler->dest.w = rounding(unit * (float)curr);
}

void Bar::Deactivate()
{
	bar->Deactivate();
	backGround->Deactivate();
	filler->Deactivate();
}

void Bar::Activate()
{
	bar->Activate();
	backGround->Activate();
	filler->Activate();
}

void Bar::Destroy()
{
	delete bar;
	delete backGround;
	delete filler;
}