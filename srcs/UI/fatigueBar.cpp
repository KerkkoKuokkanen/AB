
#include "../../hdr/global.h"
#define BAR_SOURCE_WIDTH 800.0f

FatigueBar::FatigueBar(SDL_Rect dest, bool staticSprite)
{
	bar = new Sprite(gameState.textures.smallerBar, dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
	bar->ColorMod(180, 180, 180);
	backGround = new Sprite(gameState.textures.bar[1], dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
	filler = new Sprite(gameState.textures.barFiller, dest, &sRect, NULL, 0, FLIP_NONE, staticSprite);
	shower = new Sprite(gameState.textures.barFiller, dest, &rSRect, NULL, 0, FLIP_NONE, staticSprite);
	shower->AlphaMod(140);
	filler->ColorMod(158, 83, 8);
	bar->z = 4;
	backGround->z = 1;
	shower->z = 2;
	filler->z = 3;
	bar->orderLayer = 4;
	backGround->orderLayer = 1;
	shower->orderLayer = 2;
	filler->orderLayer = 3;
	shower->ColorMod(209, 178, 0);
	FatigueBar::staticSprite = staticSprite;
	layer = (staticSprite) ? TURN_ORDER_LAYER : INFO_LAYER;
	gameState.render->AddSprite(bar, layer);
	gameState.render->AddSprite(backGround, layer);
	gameState.render->AddSprite(shower, layer);
	gameState.render->AddSprite(filler, layer);
	SDL_Rect slashDest = {dest.x + dest.w / 2 - 417, dest.y + dest.h / 2 + 150, rounding((float)dest.w / 60.0f), rounding((float)dest.h * 0.4f)};
	slash = new Sprite(gameState.textures.ascii.slash, slashDest, NULL, NULL, 0, FLIP_NONE, staticSprite);
	slash->ColorMod(250, 250, 210);
	slash->orderLayer = 5;
	gameState.render->AddSprite(slash, layer);
}

void FatigueBar::SetNumber(Character *character)
{
	int cs = character->stats.fatigue;
	int cm = character->stats.maxFatigue;
	if (cs > character->stats.maxFatigue)
		cs = character->stats.maxFatigue;
	if (cs == currStat && cm == currMax && maxStat != NULL && stat != NULL)
		return ;
	if (stat != NULL)
		delete stat;
	if (maxStat != NULL)
		delete maxStat;
	currStat = cs;
	currMax = cm;
	stat = new Number((cs < 0) ? 0 : cs, numSize, layer, 5, staticSprite, NumberType::WHITE);
	stat->ColorMod(250, 250, 210);
	int w = stat->getFullWidth();
	Vector pos((float)(slash->dest.x - w + leftNumberOffset.x), (float)(slash->dest.y + leftNumberOffset.y));
	stat->Position(pos);
	maxStat = new Number((cm < 0) ? 0 : cm, numSize, layer, 5, staticSprite, NumberType::WHITE);
	maxStat->ColorMod(250, 250, 210);
	w = maxStat->getFullWidth();
	Vector place((float)(slash->dest.x + rightNumberOffset.x), (float)(slash->dest.y + rightNumberOffset.y));
	maxStat->Position(place);
}

void FatigueBar::Setbar(Character *character)
{
	int curr = character->stats.fatigue;
	int max = character->stats.maxFatigue;
	if (curr > character->stats.maxFatigue)
		curr = character->stats.maxFatigue;
	currentFatigue = curr;
	maxFatigue = max;
	float unit = (float)bar->dest.w / (float)max;
	float sUnit = BAR_SOURCE_WIDTH / (float)max;
	sRect.w = rounding(sUnit * (float)curr);
	filler->dest.w = rounding(unit * (float)curr);
	if (sRect.w < 8 && curr > 0)
	{
		sRect.w = 8;
		filler->dest.w = 500;
	}
	if (sRect.w < 0)
	{
		sRect.w = 0;
		filler->dest.w = 0;
	}
	if (!fatigueCalled)
	{
		rSRect.w = sRect.w;
		shower->dest.w = filler->dest.w;
	}
}

void FatigueBar::CheckFatigueCalled()
{
	if (last == fatigueIter - 1)
	{
		last = fatigueIter;
		fatigueCalled = true;
	}
	else
	{
		fatigueCalled = false;
		last = 0;
		fatigueIter = 0;
	}
}

void FatigueBar::ShowFatigue(int cost)
{
	int total = currentFatigue + cost;
	fatigueIter += 1;
	if (total > maxFatigue)
	{
		total = maxFatigue;
		shower->ColorMod(120, 0, 0);
	}
	else
		shower->ColorMod(209, 178, 0);
	float fadeMulti = cos(gameState.updateObjs.fadeIter) / 2.0f + 0.5f;
	float dUnit = (float)bar->dest.w / (float)maxFatigue;
	float sUnit = BAR_SOURCE_WIDTH / (float)maxFatigue;
	rSRect.w = rounding(sUnit * (float)total);
	shower->dest.w = rounding(dUnit * (float)total);
	shower->AlphaMod(rounding(80.0f + 60.0f * fadeMulti));
}

void FatigueBar::Update(Character *character)
{
	CheckFatigueCalled();
	Setbar(character);
	SetNumber(character);
}

void FatigueBar::Deactivate()
{
	if (slash != NULL)
		slash->Deactivate();
	if (shower != NULL)
		shower->Deactivate();
	if (stat != NULL)
		stat->Deactivate();
	if (maxStat != NULL)
		maxStat->Deactivate();
	if (bar != NULL)
		bar->Deactivate();
	if (backGround != NULL)
		backGround->Deactivate();
	if (filler != NULL)
		filler->Deactivate();
}

void FatigueBar::Activate()
{
	if (slash != NULL)
		slash->Activate();
	if (shower != NULL)
		shower->Activate();
	if (stat != NULL)
		stat->Activate();
	if (maxStat != NULL)
		maxStat->Activate();
	if (bar != NULL)
		bar->Activate();
	if (backGround != NULL)
		backGround->Activate();
	if (filler != NULL)
		filler->Activate();
}

void FatigueBar::Destroy()
{
	if (slash != NULL)
		delete slash;
	if (shower != NULL)
		delete shower;
	if (stat != NULL)
		delete stat;
	if (maxStat != NULL)
		delete maxStat;
	if (bar != NULL)
		delete bar;
	if (backGround != NULL)
		delete backGround;
	if (filler != NULL)
		delete filler;
}
