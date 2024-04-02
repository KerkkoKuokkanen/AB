
#include "../../hdr/global.h"

#define BAR_SOURCE_WIDTH 800.0f

Bar::Bar(SDL_Rect dest, bool numbers, bool staticSprite)
{
	bar = new Sprite(gameState.textures.bar[0], dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
	bar->ColorMod(180, 180, 180);
	backGround = new Sprite(gameState.textures.bar[1], dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
	filler = new Sprite(gameState.textures.barFiller, dest, &sRect, NULL, 0, FLIP_NONE, staticSprite);
	reduce = new Sprite(gameState.textures.barFiller, dest, &rSRect, NULL, 0, FLIP_NONE, staticSprite);
	reduce->AlphaMod(140);
	bar->z = 5;
	backGround->z = 1;
	reduce->z = 2;
	filler->z = 3;
	bar->orderLayer = 5;
	backGround->orderLayer = 1;
	reduce->orderLayer = 2;
	filler->orderLayer = 3;
	reduce->ColorMod(209, 178, 0);
	Bar::numbers = numbers;
	Bar::staticSprite = staticSprite;
	layer = (staticSprite) ? TURN_ORDER_LAYER : INFO_LAYER;
	gameState.render->AddSprite(bar, layer);
	gameState.render->AddSprite(backGround, layer);
	gameState.render->AddSprite(reduce, layer);
	gameState.render->AddSprite(filler, layer);
	if (!numbers)
		return ;
	SDL_Rect slashDest = {dest.x + dest.w / 2 - 417, dest.y + dest.h / 2 + 150, rounding((float)dest.w / 60.0f), rounding((float)dest.h * 0.4f)};
	slash = new Sprite(gameState.textures.ascii.slash, slashDest, NULL, NULL, 0, FLIP_NONE, staticSprite);
	slash->ColorMod(250, 250, 210);
	slash->orderLayer = 5;
	gameState.render->AddSprite(slash, layer);
}

void Bar::ChangeToSmallBar()
{
	smallBar = true;
	slash->dest.w += 100;
	slash->dest.x += 200;
	slash->dest.y -= 100;
}

void Bar::GetScala()
{
	swDiff = rSRect.w - sRect.w;
	destDiff = reduce->dest.w - filler->dest.w;
}

void Bar::SetBar(int max, int curr)
{
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
	if (!healthDown)
	{
		rSRect.w = sRect.w;
		reduce->dest.w = filler->dest.w;
	}
	else
		GetScala();
}

void Bar::Position(SDL_Point place)
{
	bar->dest.x = place.x;
	bar->dest.y = place.y;
	backGround->dest.x = place.x;
	backGround->dest.y = place.y;
	filler->dest.x = place.x;
	filler->dest.y = place.y;
	reduce->dest.x = place.x;
	reduce->dest.y = place.y;
	if (!numbers)
		return ;
	slash->dest.x = place.y + bar->dest.w / 2 - 417;
	slash->dest.y = place.y + bar->dest.h / 2 + 150;
	if (stat != NULL)
	{
		int w = stat->getFullWidth();
		Vector pos((float)(slash->dest.x - 2 - 200), (float)(slash->dest.y + 360));
		stat->Position(pos);
	}
	if (maxStat != NULL)
	{
		int w = maxStat->getFullWidth();
		Vector pos((float)(slash->dest.x + 1200), (float)(slash->dest.y + 360));
		maxStat->Position(pos);
	}
}

void Bar::ChangeTextureToNarrow()
{
	bar->setTexture(gameState.textures.smallerBar);
	slash->dest.w += 300;
}

void Bar::SetSmallNumber()
{
	if (stat != NULL)
		delete stat;
	if (maxStat != NULL)
		delete maxStat;
	stat = new Number((currCurr < 0) ? 0 : currCurr, 650, layer, 5, staticSprite, NumberType::WHITE);
	stat->ColorMod(250, 250, 210);
	int w = stat->getFullWidth();
	Vector pos((float)(slash->dest.x - w + leftNumberOffset.x), (float)(slash->dest.y + leftNumberOffset.y));
	stat->Position(pos);
	maxStat = new Number((currMax < 0) ? 0 : currMax, 650, layer, 5, staticSprite, NumberType::WHITE);
	maxStat->ColorMod(250, 250, 210);
	w = maxStat->getFullWidth();
	Vector place((float)(slash->dest.x + rightNumberOffset.x), (float)(slash->dest.y + rightNumberOffset.y));
	maxStat->Position(place);
}

void Bar::SetNumber()
{
	if (smallBar)
	{
		SetSmallNumber();
		return ;
	}
	if (stat != NULL)
		delete stat;
	if (maxStat != NULL)
		delete maxStat;
	stat = new Number((currCurr < 0) ? 0 : currCurr, 800, layer, 5, staticSprite, NumberType::WHITE);
	stat->ColorMod(250, 250, 210);
	int w = stat->getFullWidth();
	Vector pos((float)(slash->dest.x - w + leftNumberOffset.x), (float)(slash->dest.y + leftNumberOffset.y));
	stat->Position(pos);
	maxStat = new Number((currMax < 0) ? 0 : currMax, 800, layer, 5, staticSprite, NumberType::WHITE);
	maxStat->ColorMod(250, 250, 210);
	w = maxStat->getFullWidth();
	Vector place((float)(slash->dest.x + rightNumberOffset.x), (float)(slash->dest.y + rightNumberOffset.y));
	maxStat->Position(place);
}

void Bar::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	colorSet = true;
	filler->ColorMod(r, g, b);
}

void Bar::ModBars(Character *target, bool health)
{
	if (target == NULL)
		return ;
	int curr, max;
	if (health)
	{
		if (!colorSet)
			filler->ColorMod(117, 6, 6);
		curr = target->stats.health;
		max = target->stats.maxHealth;
	}
	else
	{
		if (!colorSet)
			filler->ColorMod(66, 63, 82);
		curr = target->stats.armor;
		max = target->stats.maxArmor;
	}
	if ((currCurr != curr || currMax != max) || !healthDown)
	{
		currMax = max;
		currCurr = curr;
		SetBar(max, curr);
		if (numbers)
			SetNumber();
	}
}

void Bar::ManageReduce()
{
	if (!healthDown || target == NULL)
		return ;
	if (reduce->dest.w <= filler->dest.w)
		return ;
	if (healthDownTimer > 0)
	{
		healthDownTimer--;
		return ;
	}
	float sRectUnit = (float)swDiff / 35.0f;
	float destUnit = (float)destDiff / 35.0f;
	rSRect.w -= rounding(sRectUnit);
	reduce->dest.w -= rounding(destUnit);
	if (reduce->dest.w < filler->dest.w)
	{
		reduce->dest.w = filler->dest.w;
		rSRect.w = sRect.w;
	}
}

void Bar::Update(Character *target, bool health)
{
	reduce->AlphaMod(140);
	if (Bar::target == target)
		healthDown = true;
	else
	{
		healthDownTimer = 18;
		healthDown = false;
		Bar::target = target;
	}
	ModBars(target, health);
	ManageReduce();
}

void Bar::SetBarTwo(int max, int curr)
{
	float unit = (float)bar->dest.w / (float)max;
	float sUnit = BAR_SOURCE_WIDTH / (float)max;
	rSRect.w = rounding(sUnit * (float)curr);
	reduce->dest.w = rounding(unit * (float)curr);
	if (rSRect.w < 8 && curr > 0)
	{
		rSRect.w = 8;
		reduce->dest.w = 500;
	}
	if (rSRect.w < 0)
	{
		rSRect.w = 0;
		reduce->dest.w = 0;
	}
}

void Bar::SetBarThree(int max, int curr)
{
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
}

void Bar::SetNumberTwo(int min, int max)
{
	if (stat != NULL)
		delete stat;
	if (maxStat != NULL)
		delete maxStat;
	stat = new Number((min < 0) ? 0 : min, 650, layer, 5, staticSprite, NumberType::WHITE);
	stat->ColorMod(250, 250, 210);
	int w = stat->getFullWidth();
	Vector pos((float)(slash->dest.x - w + leftNumberOffset.x), (float)(slash->dest.y + leftNumberOffset.y));
	stat->Position(pos);
	maxStat = new Number((max < 0) ? 0 : max, 650, layer, 5, staticSprite, NumberType::WHITE);
	maxStat->ColorMod(250, 250, 210);
	w = maxStat->getFullWidth();
	Vector place((float)(slash->dest.x + rightNumberOffset.x), (float)(slash->dest.y + rightNumberOffset.y));
	maxStat->Position(place);
}

void Bar::ModBarsTwo(Character *target, bool health, int targetValue)
{
	if (target == NULL)
		return ;
	int curr, max, targ;
	targ = targetValue;
	if (health)
	{
		if (!colorSet)
			filler->ColorMod(117, 6, 6);
		curr = target->stats.health;
		max = target->stats.maxHealth;
	}
	else
	{
		if (!colorSet)
			filler->ColorMod(66, 63, 82);
		curr = target->stats.armor;
		max = target->stats.maxArmor;
	}
	SetBarTwo(max, curr);
	SetBarThree(max, targ);
	if (numbers)
		SetNumberTwo(curr, max);
}

void Bar::UpdateWithDMGShow(Character *target, bool health, int targetValue)
{
	ModBarsTwo(target, health, targetValue);
	float fadeMulti = cos(gameState.updateObjs.fadeIter * 2.0f) / 2.0f + 0.5f;
	float unit = 80.0f * fadeMulti;
	int amount = rounding(unit) + 60;
	reduce->AlphaMod(amount);
}

void Bar::Deactivate()
{
	target = NULL;
	bar->Deactivate();
	backGround->Deactivate();
	filler->Deactivate();
	reduce->Deactivate();
	if (!numbers)
		return ;
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
	reduce->Activate();
	if (!numbers)
		return ;
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
	delete reduce;
	if (slash != NULL)
		delete slash;
	if (stat != NULL)
		delete stat;
	if (maxStat != NULL)
		delete maxStat;
}