
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