
#include "../../../hdr/global.h"

void IconHealth::CreateBar(int curr, int max, bool red, int slot)
{
	if (curr <= 0)
		return ;
	SDL_Rect dest = {-45540, -40900, 9300, 1665};
	if (red)
		dest.y += 2200;
	dest.y += 6500 * slot;
	float unit = 9300.0f / (float)max;
	int amount = rounding(unit * (float)curr);
	dest.w = amount;
	bar[2] = new Sprite(gameState.textures.iconTexts.iconBars[1], dest, NULL, NULL, 0, FLIP_NONE, true);
	bar[2]->orderLayer = 4;
	gameState.render->AddSprite(bar[2], COUNTER_LAYER);
	if (red)
		bar[2]->ColorMod(117, 6, 6);
	else
		bar[2]->ColorMod(66, 63, 82);
}

void IconHealth::CreateReducer(int start, int curr, int max, bool red, int slot)
{
	if (start == curr)
		return ;
	SDL_Rect dest = {-45540, -40900, 9300, 1665};
	if (red)
		dest.y += 2200;
	dest.y += 6500 * slot;
	float unit = 9300.0f / (float)max;
	int amount = rounding(unit * (float)start);
	int goal = rounding(unit * (float)curr);
	goal = (goal == 0) ? 0 : goal - 1;
	reducerGoalValue = goal;
	dest.w = amount;
	reducer = new Sprite(gameState.textures.iconTexts.iconBars[1], dest, NULL, NULL, 0, FLIP_NONE, true);
	reducer->orderLayer = 3;
	gameState.render->AddSprite(reducer, COUNTER_LAYER);
	reducer->ColorMod(209, 178, 0);
	int total = amount - goal;
	scaleAmount = (float)total / 50.0f;
}

void IconHealth::Reposition(int slot)
{
	SDL_Rect dest = {-45540, -40900, 9300, 1665};
	if (red)
		dest.y += 2200;
	dest.y += 6500 * slot;
	bar[0]->dest = dest;
	bar[1]->dest = dest;
	if (reducer != NULL)
		reducer->dest.y = dest.y;
	if (bar[2] != NULL)
		bar[2]->dest.y = dest.y;
}


IconHealth::IconHealth(int start, int curr, int max, bool red, int slot)
{
	IconHealth::red = red;
	SDL_Rect dest = {-45540, -40900, 9300, 1665};
	if (red)
		dest.y += 2200;
	dest.y += 6500 * slot;
	bar[0] = new Sprite(gameState.textures.iconTexts.iconBars[0], dest, NULL, NULL, 0, FLIP_NONE, true);
	bar[1] = new Sprite(gameState.textures.iconTexts.iconBars[2], dest, NULL, NULL, 0, FLIP_NONE, true);
	bar[0]->orderLayer = 5;
	bar[1]->orderLayer = 1;
	gameState.render->AddSprite(bar[0], COUNTER_LAYER);
	gameState.render->AddSprite(bar[1], COUNTER_LAYER);
	CreateBar(curr, max, red, slot);
	CreateReducer(start, curr, max, red, slot);
}

void IconHealth::Update()
{
	if (reducer == NULL)
		return ;
	counter++;
	if (counter < 20 || atGoal)
		return ;
	reducer->dest.w -= rounding(scaleAmount);
	if (reducer->dest.w <= reducerGoalValue)
		atGoal = true;
}

void IconHealth::Destroy()
{
	if (bar[0] != NULL)
		delete bar[0];
	if (bar[1] != NULL)
		delete bar[1];
	if (bar[2] != NULL)
		delete bar[2];
	if (reducer != NULL)
		delete reducer;
}
