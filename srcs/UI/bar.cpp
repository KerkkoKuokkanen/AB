
#include "../../hdr/global.h"

#define BAR_SOURCE_WIDTH 800.0f

Bar::Bar(SDL_Rect dest)
{
	bar = new Sprite(gameState.textures.bar[0], dest, NULL, NULL, 0, FLIP_NONE, true);
	backGround = new Sprite(gameState.textures.bar[1], dest, NULL, NULL, 0, FLIP_NONE, true);
	SDL_Rect fDest = {dest.x + 200, dest.y + 200, dest.w - 400, dest.h - 400};
	filler = new Sprite(gameState.textures.barFiller, fDest, &sRect, NULL, 0, FLIP_NONE, true);
	bar->orderLayer = 3;
	backGround->orderLayer = 1;
	filler->orderLayer = 2;
	gameState.render->AddSprite(bar, TURN_ORDER_LAYER);
	gameState.render->AddSprite(backGround, TURN_ORDER_LAYER);
	gameState.render->AddSprite(filler, TURN_ORDER_LAYER);
	SDL_Rect slashDest = {dest.x + dest.w / 2 - 417, dest.y + dest.h / 2 + 200, rounding((float)dest.w / 60.0f), rounding((float)dest.h * 0.4f)};
	slash = new Sprite(gameState.textures.ascii.slash, slashDest, NULL, NULL, 0, FLIP_NONE, true);
	slash->ColorMod(190, 190, 150);
	slash->orderLayer = 4;
	gameState.render->AddSprite(slash, TURN_ORDER_LAYER);
}

void Bar::SetBar(int max, int curr)
{
	float unit = (float)bar->dest.w / (float)max;
	float sUnit = BAR_SOURCE_WIDTH / (float)max;
	sRect.w = rounding(sUnit * (float)curr);
	filler->dest.w = rounding(unit * (float)curr);
}

void Bar::SetNumber()
{
	if (stat != NULL)
		delete stat;
	if (maxStat != NULL)
		delete maxStat;
	stat = new Number(currCurr, 800, TURN_ORDER_LAYER, 4, true, NumberType::WHITE);
	stat->ColorMod(190, 190, 150);
	int w = stat->getFullWidth();
	Vector pos((float)(slash->dest.x - w - 200), (float)(slash->dest.y + 300));
	stat->Position(pos);
	maxStat = new Number(currMax, 800, TURN_ORDER_LAYER, 4, true, NumberType::WHITE);
	maxStat->ColorMod(190, 190, 150);
	w = maxStat->getFullWidth();
	Vector place((float)(slash->dest.x + 1200), (float)(slash->dest.y + 300));
	maxStat->Position(place);
}

void Bar::Update(int max, int curr, Uint8 r, Uint8 g, Uint8 b)
{
	filler->ColorMod(r, g, b);
	if (currCurr != curr || currMax != max)
	{
		currMax = max;
		currCurr = curr;
		if (max <= curr)
			filler->dest = bar->dest;
		else
			SetBar(max, curr);
		SetNumber();
	}
}

void Bar::Deactivate()
{
	bar->Deactivate();
	backGround->Deactivate();
	filler->Deactivate();
	slash->Deactivate();
	if (stat != NULL)
		stat->Deactivate();
	if (maxStat != NULL)
		maxStat->Deactivate();
}

void Bar::Activate()
{
	bar->Activate();
	backGround->Activate();
	filler->Activate();
	slash->Activate();
	if (stat != NULL)
		stat->Activate();
	if (maxStat != NULL)
		maxStat->Activate();
}

void Bar::Destroy()
{
	delete bar;
	delete backGround;
	delete filler;
	delete slash;
	if (stat != NULL)
		delete stat;
	if (maxStat != NULL)
		delete maxStat;
}