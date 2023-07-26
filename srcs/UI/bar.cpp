
#include "../../hdr/global.h"

#define BAR_SOURCE_WIDTH 800.0f

Bar::Bar(SDL_Rect dest, bool numbers, bool staticSprite)
{
	bar = new Sprite(gameState.textures.bar[0], dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
	backGround = new Sprite(gameState.textures.bar[1], dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
	filler = new Sprite(gameState.textures.barFiller, dest, &sRect, NULL, 0, FLIP_NONE, staticSprite);
	reduce = new Sprite(gameState.textures.barFiller, dest, &rSRect, NULL, 0, FLIP_NONE, staticSprite);
	bar->orderLayer = 4;
	backGround->orderLayer = 1;
	reduce->orderLayer = 2;
	filler->orderLayer = 3;
	reduce->ColorMod(209, 178, 0);
	Bar::numbers = numbers;
	Bar::staticSprite = staticSprite;
	gameState.render->AddSprite(bar, INFO_LAYER);
	gameState.render->AddSprite(backGround, INFO_LAYER);
	gameState.render->AddSprite(reduce, INFO_LAYER);
	gameState.render->AddSprite(filler, INFO_LAYER);
	if (!numbers)
		return ;
	SDL_Rect slashDest = {dest.x + dest.w / 2 - 417, dest.y + dest.h / 2 + 150, rounding((float)dest.w / 60.0f), rounding((float)dest.h * 0.4f)};
	slash = new Sprite(gameState.textures.ascii.slash, slashDest, NULL, NULL, 0, FLIP_NONE, staticSprite);
	slash->ColorMod(190, 190, 150);
	slash->orderLayer = 5;
	gameState.render->AddSprite(slash, INFO_LAYER);
}

void Bar::ChangeToSmallBar()
{
	bar->setTexture(gameState.textures.sBar[0]);
	backGround->setTexture(gameState.textures.sBar[1]);
	filler->setTexture(gameState.textures.sBar[2]);
	reduce->setTexture(gameState.textures.sBar[2]);
	sRect = {0, 0, 300, 50};
	rSRect = {0, 0, 300, 50};
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
		Vector pos((float)(slash->dest.x - 2 - 200), (float)(slash->dest.y + 300));
		stat->Position(pos);
	}
	if (maxStat != NULL)
	{
		int w = maxStat->getFullWidth();
		Vector pos((float)(slash->dest.x + 1200), (float)(slash->dest.y + 300));
		maxStat->Position(pos);
	}
}

void Bar::SetNumber()
{
	if (stat != NULL)
		delete stat;
	if (maxStat != NULL)
		delete maxStat;
	stat = new Number((currCurr < 0) ? 0 : currCurr, 800, INFO_LAYER, 5, staticSprite, NumberType::WHITE);
	stat->ColorMod(190, 190, 150);
	int w = stat->getFullWidth();
	Vector pos((float)(slash->dest.x - w - 200), (float)(slash->dest.y + 300));
	stat->Position(pos);
	maxStat = new Number((currMax < 0) ? 0 : currMax, 800, INFO_LAYER, 5, staticSprite, NumberType::WHITE);
	maxStat->ColorMod(190, 190, 150);
	w = maxStat->getFullWidth();
	Vector place((float)(slash->dest.x + 1200), (float)(slash->dest.y + 300));
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
	float sRectUnit = (float)swDiff / 30.0f;
	float destUnit = (float)destDiff / 30.0f;
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
	if (Bar::target == target)
		healthDown = true;
	else
	{
		healthDownTimer = 10;
		healthDown = false;
		Bar::target = target;
	}
	ModBars(target, health);
	ManageReduce();
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