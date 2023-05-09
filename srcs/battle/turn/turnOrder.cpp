
#include "../../../hdr/global.h"

bool compareObjects(const t_Indicator &obj1, const t_Indicator &obj2)
{
	if (obj1.character->stats.speed == obj2.character->stats.speed)
	{
		if (obj2.character->ally == false)
			return (true);
	}
	return (obj1.character->stats.speed > obj2.character->stats.speed);
}

void TurnOrder::CreateSRect(SDL_Rect *srect, int cSing)
{
	switch (cSing)
	{
		case 0:
			srect->x = 150;
			srect->y = 100;
			srect->w = 700;
			srect->h = 350;
			break ;
		case 1:
			srect->x = 350;
			srect->y = 0;
			srect->w = 350;
			srect->h = 300;
			break ;
	}
}

SDL_Rect TurnOrder::CreateDest(int cSing)
{
	SDL_Rect dest = {0, 0, 0, 0};
	switch (cSing)
	{
		case 0:
			dest = {
				rounding(((float)gameState.screen.width - ((float)gameState.screen.width / 50.0f * 33.0f))),
				0 + rounding(((float)gameState.screen.height / 50.0f)),
				rounding(((float)gameState.screen.width / 17.0f)),
				rounding(((float)gameState.screen.height / 17.0f))
			};
			break ;
		case 1:
			dest = {
				rounding(((float)gameState.screen.width - ((float)gameState.screen.width / 50.0f * 33.0f))),
				0 + rounding(((float)gameState.screen.height / 60.0f)),
				rounding(((float)gameState.screen.width / 22.0f)),
				rounding(((float)gameState.screen.height / 16.0f))
			};
	}
	return (dest);
}

void TurnOrder::ActivateTurnChange()
{
	if (turnChange || turnStartActive)
		return ;
	turnChange = true;
	bool active = false;
	for (int i = 0; i < indicators.size(); i++)
	{
		if (indicators[i].active)
			active = true;
		if (active && indicators[i].active == false)
		{
			SDL_Rect dest = indicators[i].indicator->dest;
			dest.x += rounding(((float)gameState.screen.width / 23.2f)) * 9;
			indicators[i].indicator->setDest(dest);
			indicators[i].active = true;
			return ;
		}
	}
}

void TurnOrder::CreateIndicators()
{
	for (int i = 0; i < characters.size(); i++)
	{
		SDL_Rect *srect = (SDL_Rect*)malloc(sizeof(SDL_Rect) * 1);
		CreateSRect(srect, characters[i]->cSing);
		SDL_Rect dest = CreateDest(characters[i]->cSing);
		indicators.push_back({new Sprite(characters[i]->sprite->getTexture(), dest, srect, NULL, 0, FLIP_NONE, true),
																			characters[i], srect, TURN_SIGN, false});
		indicators[i].indicator->setTranslation(false);
		indicators[i].indicator->Deactivate();
		indicators[i].indicator->orderLayer = 1;
		gameState.render->AddSprite(indicators[i].indicator, TURN_ORDER_LAYER);
	}
}

TurnOrder::TurnOrder(std::vector<Character> &characters)
{
	for (int i = 0; i < characters.size(); i++)
		TurnOrder::characters.push_back(&characters[i]);
	SDL_Rect dest = {
		rounding((float)gameState.screen.width - ((float)gameState.screen.width / 10.0f * 7.3f)),
		0 - rounding(((float)gameState.screen.height / 25.0f)),
		rounding((float)gameState.screen.width / 10.0f * 4.4f),
		rounding((float)gameState.screen.height / 6.0f)
	};
	banner = new Sprite(gameState.textures.turnOrder[0], dest, NULL, NULL, 0, FLIP_NONE, true);
	banner->setTranslation(false);
	banner->orderLayer = 2;
	backGround = new Sprite(gameState.textures.turnOrder[1], dest, NULL, NULL, 0, FLIP_NONE, true);
	backGround->orderLayer = 0;
	backGround->setTranslation(false);
	gameState.render->AddSprite(backGround, TURN_ORDER_LAYER);
	gameState.render->AddSprite(banner, TURN_ORDER_LAYER);
	gameState.updateObjs.turnOrder = this;
	leftEdge = rounding((float)gameState.screen.width - ((float)gameState.screen.width / 10.0f * 7.5f));
	rightEdge = leftEdge + rounding((float)gameState.screen.width / 10.0f * 4.44f);
	CreateIndicators();
	StartTurn(); // this is temporarily here
}

void TurnOrder::StartTurn()
{
	turnStartActive = true;
	std::sort(indicators.begin(), indicators.end(), compareObjects);
	int posDiff = rounding(((float)gameState.screen.width / 23.2f));
	for (int i = 0; i < indicators.size() && i < posCount; i++)
	{
		Vector place(
			(float)(indicators[i].indicator->dest.x + (posDiff * i)) + (float)gameState.screen.width / 2.5f,
			(float)(indicators[i].indicator->dest.y)
		);
		indicators[i].indicator->dest = CreateDest(indicators[i].character->cSing);
		CreateSRect(indicators[i].srect, indicators[i].character->cSing);
		indicators[i].indicator->Activate();
		indicators[i].indicator->Position(place);
		indicators[i].active = true;
	}
}

void TurnOrder::RightEdgeManage(t_Indicator &indicator)
{
	SDL_Rect dest = indicator.indicator->dest;
	if (dest.x >= rightEdge)
	{
		indicator.indicator->AlphaMod(0);
		return ;
	}
	indicator.indicator->ClearAlphaMod();
	float unit = (float)indicator.srect->w / (float)indicator.indicator->dest.w;
	int max = CreateDest(indicator.character->cSing).w;
	int len = rightEdge - dest.x;
	if (len >= max)
	{
		indicator.indicator->dest.w = max;
		CreateSRect(indicator.srect, indicator.character->cSing);
		return ;
	}
	indicator.indicator->dest.w = len;
	indicator.srect->w = (int)(unit * (float)len);
}

void TurnOrder::UpdateStartTurn()
{
	int posDiff = rounding(((float)gameState.screen.width / 23.2f));
	float unit = 4000.0f / ((float)gameState.screen.width / 2.5f);
	for (int i = 0; i < indicators.size() && i < posCount; i++)
	{
		int target = CreateDest(indicators[i].character->cSing).x + (posDiff * i);
		SDL_Rect dest = indicators[i].indicator->dest;
		if ((int)indicators[i].x == TURN_SIGN)
			indicators[i].x = (float)dest.x;
		if (dest.x <= target)
		{
			turnStartActive = false;
			return ;
		}
		float len = indicators[i].x - (float)target;
		indicators[i].x -= (float)gameState.screen.width / (4050.0f - (unit * len));
		indicators[i].indicator->Position(Vector(indicators[i].x, (float)dest.y));
		RightEdgeManage(indicators[i]);
	}
}

void TurnOrder::ChangeTurn()
{
	int i = 0, k = 0;
	int posDiff = rounding(((float)gameState.screen.width / 23.2f));
	while (indicators[i].active == false && i < indicators.size())
		i++;
	while (indicators[i].active == true && i < indicators.size())
	{
		int target = CreateDest(indicators[i].character->cSing).x + (posDiff * (k - 1));
		SDL_Rect dest = indicators[i].indicator->dest;
		if ((int)indicators[i].x == TURN_SIGN)
			indicators[i].x = (float)dest.x;
		if (dest.x <= target && k == 0)
		{
			turnChange = false;
			indicators[i].active = false;
			break ;
		}
		indicators[i].x -= (float)gameState.screen.width / 5000.0f;
		indicators[i].indicator->Position(Vector(indicators[i].x, (float)dest.y));
		RightEdgeManage(indicators[i]);
		i++; k++;
	}
}

void TurnOrder::Update()
{
	bool active = false;
	for (int i = 0; i < indicators.size(); i++)
	{
		indicators[i].character->turn = false;
		if (!indicators[i].active)
			indicators[i].indicator->Deactivate();
		else
		{
			if (!active)
			{
				indicators[i].character->turn = true;
				active = true;
			}
			indicators[i].indicator->Activate();
		}
		if (turnStartActive)
			UpdateStartTurn();
		if (turnChange)
			ChangeTurn();
	}
}

void TurnOrder::Destroy()
{
	delete banner;
	delete backGround;
	for (int i = 0; i < indicators.size(); i++)
	{
		delete indicators[i].indicator;
		free(indicators[i].srect);
	}
	indicators.clear();
	characters.clear();
	gameState.updateObjs.turnOrder = NULL;
}
