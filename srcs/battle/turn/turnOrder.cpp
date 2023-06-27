
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

bool TurnOrder::NoOneMoving()
{
	for (int i = 0; i < indicators.size(); i++)
	{
		if (indicators[i].character->moving)
			return (false);
	}
	return (true);
}

void TurnOrder::ActivateTurnChange()
{
	if (turnChange || turnStartActive || killActive || !NoOneMoving())
		return ;
	bool visited = false;
	for (int i = 0; i < indicators.size(); i++)
	{
		if (indicators[i].active)
			visited = true;
		if (indicators[i].character->killed)
			return ;
	}
	if (!visited)
		return ;
	turnChange = true;
	ResetClicks();
	gameState.updateObjs.indicator->Deactivate();
	int posDiff = rounding(((float)gameState.screen.width / 23.2f));
	int index = findTheFirstActive();
	int hold = index;
	int k = 0;
	while (index < indicators.size())
	{
		SDL_Rect dest = CreateDest(indicators[index].character->cSing);
		dest.x += k * posDiff;
		indicators[index].x = dest.x;
		indicators[index].indicator->Position(Vector(dest.x, dest.y));
		SideManage(indicators[index]);
		index++;
		k++;
	}
	target = indicators[hold].indicator->dest.x - posDiff;
	wait = 25;
}

void TurnOrder::CreateIndicators()
{
	for (int i = 0; i < characters.size(); i++)
	{
		SDL_Rect *srect = (SDL_Rect*)malloc(sizeof(SDL_Rect) * 1);
		CreateSRect(srect, characters[i]->cSing);
		SDL_Rect dest = CreateDest(characters[i]->cSing);
		indicators.push_back({new Sprite(characters[i]->sprite->getTexture(), dest, srect, NULL, 0, FLIP_NONE, true),
																		characters[i], srect, TURN_SIGN, false, 0});
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
		rounding((float)gameState.screen.width / 10.0f * 4.41f),
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
	gameState.updateObjs.turnOrder = this; //remember to implement a working singleton here
	leftEdge = rounding((float)gameState.screen.width - ((float)gameState.screen.width / 10.0f * 7.5f));
	rightEdge = leftEdge + rounding((float)gameState.screen.width / 10.0f * 4.44f);
	clickBoxArea = {
		dest.x + rounding((float)gameState.screen.width / 13.9f),
		dest.y + rounding((float)gameState.screen.height / 16.0f),
		dest.w - rounding((float)gameState.screen.width / 10.0f),
		dest.h - rounding((float)gameState.screen.height / 9.5f)
	};
	CreateIndicators();
	StartTurn(); // this is temporarily here
}

void TurnOrder::StartTurn()
{
	turnStartActive = true;
	std::sort(indicators.begin(), indicators.end(), compareObjects);
	for (int i = 0; i < indicators.size(); i++)
	{
		indicators[i].character->moves += 9;
		if (indicators[i].character->moves > 12)
			indicators[i].character->moves = 12;
	}
	int posDiff = rounding(((float)gameState.screen.width / 23.2f));
	for (int i = 0; i < indicators.size(); i++)
	{
		indicators[i].indicator->dest = CreateDest(indicators[i].character->cSing);
		Vector place(
			(float)(indicators[i].indicator->dest.x + (posDiff * i)) + (float)gameState.screen.width / 2.5f,
			(float)(indicators[i].indicator->dest.y)
		);
		CreateSRect(indicators[i].srect, indicators[i].character->cSing);
		indicators[i].indicator->Activate();
		indicators[i].indicator->Position(place);
		indicators[i].active = true;
		indicators[i].x = TURN_SIGN;
	}
}

void TurnOrder::SideManage(t_Indicator &indicator)
{
	if (!LeftEdgeManage(indicator) && !RightEdgeManage(indicator))
		indicator.indicator->ClearAlphaMod();
}

bool TurnOrder::LeftEdgeManage(t_Indicator &indicator)
{
	int point = rounding((float)gameState.screen.width / 3.45f);
	if (indicator.indicator->dest.x <= point)
	{
		indicator.indicator->AlphaMod(0);
		return (true);
	}
	return (false);
}

bool TurnOrder::RightEdgeManage(t_Indicator &indicator)
{
	SDL_Rect dest = indicator.indicator->dest;
	if (dest.x >= rightEdge)
	{
		indicator.indicator->AlphaMod(0);
		return (true);
	}
	float unit = (float)indicator.srect->w / (float)indicator.indicator->dest.w;
	int max = CreateDest(indicator.character->cSing).w;
	int len = rightEdge - dest.x;
	if (len >= max)
	{
		indicator.indicator->dest.w = max;
		CreateSRect(indicator.srect, indicator.character->cSing);
		return (false);
	}
	indicator.indicator->dest.w = len;
	indicator.srect->w = (int)(unit * (float)len);
	return (false);
}

void TurnOrder::UpdateStartTurn()
{
	int posDiff = rounding(((float)gameState.screen.width / 23.2f));
	float unit = 600.0f / ((float)gameState.screen.width / 2.5f);
	for (int i = 0; i < indicators.size(); i++)
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
		indicators[i].x -= (float)gameState.screen.width / (650.0f - (unit * len));
		indicators[i].indicator->Position(Vector(indicators[i].x, (float)dest.y));
		SideManage(indicators[i]);
	}
}

void TurnOrder::ChangeTurn()
{
	if (wait > 0)
	{
		wait--;
		return ;
	}
	int i = findTheFirstActive(), k = 0;
	int posDiff = rounding(((float)gameState.screen.width / 23.2f));
	bool atEnd = false;
	while (i < indicators.size())
	{
		SDL_Rect dest = indicators[i].indicator->dest;
		if ((int)indicators[i].x == TURN_SIGN)
			indicators[i].x = (float)dest.x;
		if (dest.x <= target && k == 0)
		{
			atEnd = true;
			turnChange = false;
			target = TARGET_SIGN;
			break ;
		}
		indicators[i].x -= (float)gameState.screen.width / 600.0f;
		indicators[i].indicator->Position(Vector(indicators[i].x, (float)dest.y));
		SideManage(indicators[i]);
		i++; k++;
	}
	if (!atEnd)
		return ;
	for (int j = 0; j < indicators.size(); j++)
	{
		if (indicators[j].active)
		{
			indicators[j].active = false;
			return ;
		}
	}
}

void TurnOrder::ResetClicks()
{
	for (int i = 0; i < indicators.size(); i++)
		indicators[i].character->clicked = false;
}

void TurnOrder::CheckClickBox()
{
	if (gameState.keys.middleMouse == 1 || killActive || gameState.updateObjs.hover.overMenu)
	{
		insideBox = false;
		return ;
	}
	SDL_Point pos = {gameState.keys.staticMouseX, gameState.keys.staticMouseY};
	insideBox = MenuHoverCheck(gameState.surfaces.turnOrder[0], banner->dest, gameState.keys.staticMouseX, gameState.keys.staticMouseY);
	if (!insideBox)
		insideBox = MenuHoverCheck(gameState.surfaces.turnOrder[1], backGround->dest, gameState.keys.staticMouseX, gameState.keys.staticMouseY);
	if (!insideBox || stuffHappening)
		return ;
	int posDiff = rounding(((float)gameState.screen.width / 23.2f));
	SDL_Rect box = {
		0,
		clickBoxArea.y,
		posDiff,
		clickBoxArea.h
	};
	for (int i = 0; i < indicators.size(); i++)
	{
		if (indicators[i].character->killed || indicators[i].character->moving)
			continue ;
		box.x = indicators[i].indicator->dest.x;
		if (pointCheck(pos, box))
		{
			SDL_Point place = gameState.updateObjs.indicator->FindCharacter(indicators[i].character);
			if (!gameState.battle.ground->map[place.y][place.x].highlited)
			{
				if (indicators[i].character->ally)
					gameState.battle.ground->HighLightBlock(place, 120, 255, 100);
				else
					gameState.battle.ground->HighLightBlock(place, 255, 69, 56);
			}
			if (gameState.keys.click == RELEASE_CLICK && !gameState.updateObjs.abilities->active)
			{
				ResetClicks();
				indicators[i].character->clicked = true;
			}
			return ;
		}
	}
}

int TurnOrder::findTheFirstActive()
{
	int ret = (-1);
	for (int i = 0; i < indicators.size(); i++)
	{
		if (indicators[i].active)
		{
			ret = i;
			break ;
		}
	}
	return (ret);
}

void TurnOrder::MouseScroll()
{
	if (stuffHappening)
		return ;
	if (gameState.keys.wheel == 0)
		return ;
	if (!insideBox)
		return ;
	int index = findTheFirstActive();
	if (index == (-1))
		return ;
	int dir = (gameState.keys.wheel < 0) ? gameState.keys.wheel / gameState.keys.wheel * (-1) : gameState.keys.wheel / gameState.keys.wheel;
	int unit = rounding((float)gameState.screen.width / 250.0f);
	dir = dir * unit;
	int pos = CreateDest(indicators[index].character->cSing).x;
	if (dir > 0)
	{
		if (indicators[index].indicator->dest.x >= pos)
			return ;
		if (pos - indicators[index].indicator->dest.x < unit)
			dir = pos - indicators[index].indicator->dest.x;
	}
	int dos = CreateDest(indicators[indicators.size() - 1].character->cSing).x;
	if (dir < 0)
	{
		if (indicators[indicators.size() - 1].indicator->dest.x <= dos)
			return ;
		if (indicators[indicators.size() - 1].indicator->dest.x - dos < unit)
			dir = (indicators[indicators.size() - 1].indicator->dest.x - dos) * (-1);
	}
	for (int i = 0; i < indicators.size(); i++)
	{
		indicators[i].indicator->dest.x += dir;
		indicators[i].x += dir;
		SideManage(indicators[i]);
	}
}

void TurnOrder::RemoveCharacter(Character *character)
{
	killActive = true;
	for (int i = 0; i < characters.size(); i++)
	{
		if (characters[i] == character)
		{
			characters.erase(characters.begin() + i);
			break ;
		}
	}
	int index = 0;
	for (int i = 0; i < indicators.size(); i++)
	{
		if (indicators[i].character == character)
		{
			if (indicators[i].character->turn)
			{
				if (target == TARGET_SIGN)
					target = indicators[i].indicator->dest.x;
			}
			delete indicators[i].indicator;
			free(indicators[i].srect);
			indicators.erase(indicators.begin() + i);
			index = i;
			break ;
		}
	}
	while (index < indicators.size())
	{
		indicators[index].killMove += 1;
		index++;
	}
}

void TurnOrder::KillMoveUpdate()
{
	int iter = 0;
	int targ = 0;
	int posDiff = rounding(((float)gameState.screen.width / 23.2f));
	while (iter < indicators.size())
	{
		if (indicators[iter].killMove > 0)
			break ;
		targ = indicators[iter].indicator->dest.x + posDiff;
		iter++;
	}
	if (targ == 0 && indicators.size() != 0)
		targ = target;
	if (iter == indicators.size())
	{
		target = TARGET_SIGN;
		killActive = false;
		return ;
	}
	bool atEnd = false;
	for (int i = 0; i < indicators.size(); i++)
	{
		if (indicators[i].killMove <= 0)
			continue ;
		if ((int)indicators[i].x == TURN_SIGN)
			indicators[i].x = (float)indicators[i].indicator->dest.x;
		if (indicators[i].x <= targ)
		{
			atEnd = true;
			break ;
		}
		indicators[i].x -= (float)gameState.screen.width / 600.0f;
		indicators[i].indicator->Position(Vector(indicators[i].x, (float)indicators[i].indicator->dest.y));
		SideManage(indicators[i]);
	}
	if (!atEnd)
		return ;
	for (int i = 0; i < indicators.size(); i++)
	{
		if (indicators[i].killMove > 0)
			indicators[i].killMove -= 1;
	}
}

void TurnOrder::SetStuffWithoudMove()
{
	if (turnChange || turnStartActive)
	{
		stuffWithOutMove = true;
		return ;
	}
	stuffWithOutMove = false;
}

void TurnOrder::SetStuffHappening()
{
	if (turnChange || turnStartActive || killActive || !NoOneMoving())
	{
		stuffHappening = true;
		return ;
	}
	for (int i = 0; i < indicators.size() - 1; i++)
	{
		if (indicators[i].character->killed)
		{
			stuffHappening = true;
			return ;
		}
	}
	stuffHappening = false;
}

void TurnOrder::Update()
{
	bool active = false;
	bool visited = false;
	SetStuffHappening();
	SetStuffWithoudMove();
	gameState.updateObjs.indicator->Deactivate();
	for (int i = 0; i < indicators.size(); i++)
	{
		indicators[i].character->turn = false;
		if (!indicators[i].active)
			indicators[i].indicator->Deactivate();
		else
		{
			visited = true;
			if (!active && !turnChange && !turnStartActive)
			{
				indicators[i].character->turn = true;
				active = true;
				if (!stuffWithOutMove)
					gameState.updateObjs.indicator->SetCharacter(indicators[i].character);
			}
			indicators[i].indicator->Activate();
		}
	}
	if (!visited)
		StartTurn();
	if (turnStartActive)
		UpdateStartTurn();
	if (turnChange)
		ChangeTurn();
	if (killActive)
		KillMoveUpdate();
	CheckClickBox();
	MouseScroll();
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
