
#include "../../hdr/global.h"

Bar::Bar(SDL_Rect dest)
{
	bar = new Sprite(gameState.textures.bar[0], dest, NULL, NULL, 0, FLIP_NONE, true);
	backGround = new Sprite(gameState.textures.bar[1], dest, NULL, NULL, 0, FLIP_NONE, true);
	filler = new Sprite(gameState.textures.barFiller, dest, NULL, NULL, 0, FLIP_NONE, true);
	bar->setTranslation(false);
	backGround->setTranslation(false);
	filler->setTranslation(false);
	bar->orderLayer = 2;
	backGround->orderLayer = 0;
	filler->orderLayer = 1;
	gameState.render->AddSprite(bar, TURN_ORDER_LAYER);
	gameState.render->AddSprite(backGround, TURN_ORDER_LAYER);
	gameState.render->AddSprite(filler, TURN_ORDER_LAYER);
}

void Bar::Update(int max, int curr, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Rect dest = {
		bar->dest.x + (int)((float)bar->dest.x / 10.0f),
		bar->dest.y + (int)((float)bar->dest.y / 10.0f),
		bar->dest.w - (int)((float)bar->dest.w / 10.0f),
		bar->dest.h - (int)((float)bar->dest.h / 10.0f)
	};
	filler->dest = dest;
	filler->ColorMod(r, g, b);
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