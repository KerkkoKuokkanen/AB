
#include "../../../hdr/global.h"
#define ICON_BAR_TIME 135

IconBar::IconBar(Character *target, int slot, int aStart, int a, int hStart, int h)
{
	IconBar::target = target;
	IconBar::slot = slot;
	counter = ICON_BAR_TIME;
	SDL_Rect dest = {-48700, -41000, 3000, 3000};
	SDL_Rect dest2 = {-48800, -41200, 12700, 3280};
	dest.y += 6500 * slot;
	dest2.y += 6500 * slot;
	iconBlock = new Sprite(gameState.textures.iconTexts.icons[target->cSing], dest, NULL, NULL, 0, FLIP_NONE, true);
	iconBlock->orderLayer = 10;
	gameState.render->AddSprite(iconBlock, COUNTER_LAYER);
	backGround = new Sprite(gameState.textures.everyColor, dest2, NULL, NULL, 0, FLIP_NONE, true);
	backGround->ColorMod(1, 1, 1);
	gameState.render->AddSprite(backGround, COUNTER_LAYER);
	bars[0] = new IconHealth(aStart, a, target->stats.maxArmor, false, slot);
	bars[1] = new IconHealth(hStart, h, target->stats.maxHealth, true, slot);
	if (h <= 0)
	{
		IconBar::target = NULL;
		crossing = true;
	}
}

void IconBar::RePosition(int slot)
{
	IconBar::slot = slot;
	SDL_Rect dest = {-48700, -41000, 3000, 3000};
	SDL_Rect dest2 = {-48800, -41100, 12700, 3200};
	dest.y += 6500 * slot;
	dest2.y += 6500 * slot;
	iconBlock->dest = dest;
	backGround->dest = dest2;
	if (CrossSprites[0] != NULL)
		CrossSprites[0]->dest.y = dest.y;
	if (CrossSprites[1] != NULL)
		CrossSprites[1]->dest.y = dest2.y;
	bars[0]->Reposition(slot);
	bars[1]->Reposition(slot);
}

void IconBar::CreateCrosses()
{
	SDL_Rect dest = {-48700, -41000, 0, 3000};
	SDL_Rect dest2 = {-45700, -41000, 0, 3000};
	dest.y += 6500 * slot;
	dest2.y += 6500 * slot;
	CrossSprites[0] = new Sprite(gameState.textures.iconTexts.iconX, dest, &CrossigRects[0], NULL, 0, FLIP_NONE, true);
	CrossSprites[1] = new Sprite(gameState.textures.iconTexts.iconX, dest2, &CrossigRects[1], NULL, 0, FLIP_NONE, true);
	CrossSprites[0]->orderLayer = 11;
	CrossSprites[1]->orderLayer = 11;
	gameState.render->AddSprite(CrossSprites[0], COUNTER_LAYER);
	gameState.render->AddSprite(CrossSprites[1], COUNTER_LAYER);
}

void IconBar::UpdateCrossing()
{
	if (counter > 110 || counter < 70 || crossing == false)
		return ;
	if (counter == 110)
		CreateCrosses();
	int count = (counter - 110) * (-1);
	float unit = 64.0f / 40.0f;
	float wUnit = 3000.0f / 40.0f;
	int amount = rounding(unit * (float)count);
	int wAmount = rounding(wUnit * (float)count);
	if (amount > 64)
		amount = 64;
	CrossSprites[0]->dest.w = wAmount;
	CrossSprites[1]->dest.w = wAmount;
	CrossSprites[1]->dest.x = -45700 - wAmount;
	CrossigRects[0].w = amount;
	CrossigRects[1].x = 64 - amount;
	CrossigRects[1].w = amount;
}

void IconBar::Update()
{
	if (done)
		return ;
	UpdateCrossing();
	bars[0]->Update();
	bars[1]->Update();
	counter--;
	if (counter <= 0)
		done = true;
}

void IconBar::Destroy()
{
	if (iconBlock != NULL)
		delete iconBlock;
	if (backGround != NULL)
		delete backGround;
	if (CrossSprites[0] != NULL)
		delete CrossSprites[0];
	if (CrossSprites[1] != NULL)
		delete CrossSprites[1];
	if (bars[0] != NULL)
		delete bars[0];
	if (bars[1] != NULL)
		delete bars[1];
}
