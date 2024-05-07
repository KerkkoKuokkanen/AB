
#include "../../../hdr/global.h"
#include "../../../hdr/render/camera.h"

static bool compareObjects(const t_Indicator &obj1, const t_Indicator &obj2)
{
	if (obj1.character->stats.speed == obj2.character->stats.speed)
	{
		if (obj1.character->ally)
			return (true);
	}
	return (obj1.character->stats.speed > obj2.character->stats.speed);
}

static SDL_Texture *getCharacterTexture(Character *character)
{
	if (character->cSing != MAGE && character->cSing != WITCH && character->cSing != BIG_THUG)
		return (character->sprite->getTexture());
	if (character->cSing == MAGE)
		return (gameState.textures.chars.mageIndicator);
	if (character->cSing == BIG_THUG)
		return (gameState.textures.chars.bigThugIndicator);
	return (gameState.textures.chars.witchSource);
}

void TurnOrder::CreateSRect(SDL_Rect *srect, int cSing)
{
	switch (cSing)
	{
		case THIEF:
			srect->x = 320;
			srect->y = 70;
			srect->w = 340;
			srect->h = 350;
			break ;
		case SKELE:
			srect->x = 350;
			srect->y = 0;
			srect->w = 350;
			srect->h = 300;
			break ;
		case PYRO:
			srect->x = 280;
			srect->y = 65;
			srect->w = 320;
			srect->h = 363;
			break ;
		case LION:
			srect->x = 227;
			srect->y = 60;
			srect->w = 455;
			srect->h = 440;
			break ;
		case SMITH:
			srect->x = 200;
			srect->y = 68;
			srect->w = 474;
			srect->h = 473;
			break ;
		case MAGE:
			srect->x = 280;
			srect->y = 105;
			srect->w = 330;
			srect->h = 323;
			break ;
		case RAIDER:
			srect->x = 200;
			srect->y = 115;
			srect->w = 415;
			srect->h = 400;
			break ;
		case ALCHEMIST:
			srect->x = 240;
			srect->y = 65;
			srect->w = 360;
			srect->h = 363;
			break ;
		case KNIGHT:
			srect->x = 240;
			srect->y = 44;
			srect->w = 400;
			srect->h = 403;
			break ;
		case WITCH:
			srect->x = 285;
			srect->y = 30;
			srect->w = 310;
			srect->h = 313;
			break ;
		case BIG_THUG:
			srect->x = 0;
			srect->y = 0;
			srect->w = 299;
			srect->h = 299;
			break ;
		case THUG:
			srect->x = 335;
			srect->y = 100;
			srect->w = 310;
			srect->h = 313;
			break ;
	}
}

SDL_Rect TurnOrder::CreateDest(int cSing)
{
	SDL_Rect dest = {0, 0, 0, 0};
	switch (cSing)
	{
		case THIEF:
			dest = {
				rounding(((float)gameCamera.screen.width - ((float)gameCamera.screen.width / 50.0f * 32.9f))),
				0 + rounding(((float)gameCamera.screen.height / 50.0f)),
				rounding(((float)gameCamera.screen.width / 26.0f)),
				rounding(((float)gameCamera.screen.height / 17.0f))
			};
			break ;
		case SKELE:
			dest = {
				rounding(((float)gameCamera.screen.width - ((float)gameCamera.screen.width / 50.0f * 33.0f))),
				0 + rounding(((float)gameCamera.screen.height / 60.0f)),
				rounding(((float)gameCamera.screen.width / 22.0f)),
				rounding(((float)gameCamera.screen.height / 16.0f))
			};
			break ;
		case PYRO:
			dest = {
				rounding(((float)gameCamera.screen.width - ((float)gameCamera.screen.width / 50.0f * 33.0f))),
				0 + rounding(((float)gameCamera.screen.height / 50.0f)),
				rounding(((float)gameCamera.screen.width / 26.0f)),
				rounding(((float)gameCamera.screen.height / 17.0f))
			};
			break ;
		case LION:
			dest = {
				rounding(((float)gameCamera.screen.width - ((float)gameCamera.screen.width / 50.0f * 32.82f))),
				0 + rounding(((float)gameCamera.screen.height / 50.0f)),
				rounding(((float)gameCamera.screen.width / 26.0f)),
				rounding(((float)gameCamera.screen.height / 17.0f))
			};
			break ;
		case SMITH:
			dest = {
				rounding(((float)gameCamera.screen.width - ((float)gameCamera.screen.width / 50.0f * 32.8f))),
				0 + rounding(((float)gameCamera.screen.height / 50.0f)),
				rounding(((float)gameCamera.screen.width / 26.0f)),
				rounding(((float)gameCamera.screen.height / 17.0f))
			};
			break ;
		case MAGE:
			dest = {
				rounding(((float)gameCamera.screen.width - ((float)gameCamera.screen.width / 50.0f * 32.8f))),
				0 + rounding(((float)gameCamera.screen.height / 50.0f)),
				rounding(((float)gameCamera.screen.width / 26.0f)),
				rounding(((float)gameCamera.screen.height / 17.0f))
			};
			break ;
		case RAIDER:
			dest = {
				rounding(((float)gameCamera.screen.width - ((float)gameCamera.screen.width / 50.0f * 32.9f))),
				0 + rounding(((float)gameCamera.screen.height / 50.0f)),
				rounding(((float)gameCamera.screen.width / 26.0f)),
				rounding(((float)gameCamera.screen.height / 17.0f))
			};
			break ;
		case ALCHEMIST:
			dest = {
				rounding(((float)gameCamera.screen.width - ((float)gameCamera.screen.width / 50.0f * 32.9f))),
				0 + rounding(((float)gameCamera.screen.height / 50.0f)),
				rounding(((float)gameCamera.screen.width / 26.0f)),
				rounding(((float)gameCamera.screen.height / 17.0f))
			};
			break ;
		case KNIGHT:
			dest = {
				rounding(((float)gameCamera.screen.width - ((float)gameCamera.screen.width / 50.0f * 32.9f))),
				0 + rounding(((float)gameCamera.screen.height / 50.0f)),
				rounding(((float)gameCamera.screen.width / 26.0f)),
				rounding(((float)gameCamera.screen.height / 17.0f))
			};
			break ;
		case WITCH:
			dest = {
				rounding(((float)gameCamera.screen.width - ((float)gameCamera.screen.width / 50.0f * 32.9f))),
				0 + rounding(((float)gameCamera.screen.height / 50.0f)),
				rounding(((float)gameCamera.screen.width / 26.0f)),
				rounding(((float)gameCamera.screen.height / 17.0f))
			};
			break ;
		case BIG_THUG:
			dest = {
				rounding(((float)gameCamera.screen.width - ((float)gameCamera.screen.width / 50.0f * 32.9f))),
				0 + rounding(((float)gameCamera.screen.height / 50.0f)),
				rounding(((float)gameCamera.screen.width / 26.0f)),
				rounding(((float)gameCamera.screen.height / 17.0f))
			};
			break ;
		case THUG:
			dest = {
				rounding(((float)gameCamera.screen.width - ((float)gameCamera.screen.width / 50.0f * 32.9f))),
				0 + rounding(((float)gameCamera.screen.height / 50.0f)),
				rounding(((float)gameCamera.screen.width / 26.0f)),
				rounding(((float)gameCamera.screen.height / 17.0f))
			};
			break ;
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

void TurnOrder::ActivateTurnChange(bool force)
{
	if (!force && gameState.updateObjs.abilities->active)
		return ;
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
	int posDiff = rounding(((float)gameCamera.screen.width / 23.2f));
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
	wait = 6;
}

void TurnOrder::CreateIndicators()
{
	for (int i = 0; i < characters.size(); i++)
	{
		SDL_Rect *srect = (SDL_Rect*)malloc(sizeof(SDL_Rect) * 1);
		CreateSRect(srect, characters[i]->cSing);
		SDL_Rect dest = CreateDest(characters[i]->cSing);
		SDL_Texture *indicatorTexture = getCharacterTexture(characters[i]);
		indicators.push_back({new Sprite(indicatorTexture, dest, srect, NULL, 0, FLIP_NONE, true),
																		characters[i], srect, TURN_SIGN, false, 0});
		indicators[i].indicator->setTranslation(false);
		indicators[i].indicator->Deactivate();
		indicators[i].indicator->orderLayer = 1;
		gameState.render->AddSprite(indicators[i].indicator, TURN_ORDER_LAYER);
	}
}

TurnOrder::TurnOrder(std::vector<Character> &characters)
{
	int www = rounding(gameCamera.screen.width / 50.0f);
	int hhh = rounding(gameCamera.screen.height / 44.0f);
	int yyy = rounding(gameCamera.screen.height / 300.0f);
	hoverIndicator = new Sprite(gameState.textures.turnIndicator, {0, yyy, www, hhh}, NULL, NULL, 0, FLIP_NONE, true);
	hoverIndicator->setTranslation(false);
	hoverIndicator->orderLayer = 5;
	gameState.render->AddSprite(hoverIndicator, TURN_ORDER_LAYER);
	hoverIndicator->Deactivate();
	for (int i = 0; i < characters.size(); i++)
		TurnOrder::characters.push_back(&characters[i]);
	SDL_Rect dest = {
		rounding((float)gameCamera.screen.width - ((float)gameCamera.screen.width / 10.0f * 7.3f)),
		0 - rounding(((float)gameCamera.screen.height / 25.0f)),
		rounding((float)gameCamera.screen.width / 10.0f * 4.41f),
		rounding((float)gameCamera.screen.height / 6.0f)
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
	leftEdge = rounding((float)gameCamera.screen.width - ((float)gameCamera.screen.width / 10.0f * 7.5f));
	rightEdge = leftEdge + rounding((float)gameCamera.screen.width / 10.0f * 4.44f);
	clickBoxArea = {
		dest.x + rounding((float)gameCamera.screen.width / 13.9f),
		dest.y + rounding((float)gameCamera.screen.height / 16.0f),
		dest.w - rounding((float)gameCamera.screen.width / 10.0f),
		dest.h - rounding((float)gameCamera.screen.height / 9.5f)
	};
	CreateIndicators();
	std::sort(indicators.begin(), indicators.end(), compareObjects);
	StartTurn(); // this is temporarily here
}

void TurnOrder::StartTurn()
{
	PlaySound(gameState.audio.turnStart, Channels::TURN_START, 0);
	turnCount += 1;
	turnStartActive = true;
	int posDiff = rounding(((float)gameCamera.screen.width / 23.2f));
	for (int i = 0; i < indicators.size(); i++)
	{
		indicators[i].indicator->dest = CreateDest(indicators[i].character->cSing);
		Vector place(
			(float)(indicators[i].indicator->dest.x + (posDiff * i)) + (float)gameCamera.screen.width / 2.5f,
			(float)(indicators[i].indicator->dest.y)
		);
		CreateSRect(indicators[i].srect, indicators[i].character->cSing);
		indicators[i].indicator->Activate();
		indicators[i].indicator->Position(place);
		indicators[i].active = true;
		indicators[i].x = TURN_SIGN;
	}
	UpdateStartTurn();
}

void TurnOrder::SideManage(t_Indicator &indicator)
{
	if (!LeftEdgeManage(indicator) && !RightEdgeManage(indicator))
		indicator.indicator->ClearAlphaMod();
}

bool TurnOrder::LeftEdgeManage(t_Indicator &indicator)
{
	int point = rounding((float)gameCamera.screen.width / 3.45f);
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
	int posDiff = rounding(((float)gameCamera.screen.width / 23.2f));
	float unit = 600.0f / ((float)gameCamera.screen.width / 2.0f);
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
		indicators[i].x -= (float)gameCamera.screen.width / (500.0f - (unit * len));
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
	int posDiff = rounding(((float)gameCamera.screen.width / 23.2f));
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
		indicators[i].x -= (float)gameCamera.screen.width / 500.0f;
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
	int posDiff = rounding(((float)gameCamera.screen.width / 23.2f));
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
			SDL_Point place = indicators[i].character->position;
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
	int unit = rounding((float)gameCamera.screen.width / 250.0f);
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
	if (character->cSing == PHANTOM_LION || character->cSing == TOOLS)
		return ;
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
	bool visited = false;
	for (int i = 0; i < indicators.size(); i++)
	{
		if (indicators[i].character == character)
		{
			if (indicators[i].character->turn)
			{
				if (target == TARGET_SIGN)
					target = indicators[i].indicator->dest.x;
			}
			int point = rounding((float)gameCamera.screen.width / 3.2f);
			if (indicators[i].indicator->dest.x <= point)
			{
				killActive = false;
				target = TARGET_SIGN;
				visited = true;
			}
			delete indicators[i].indicator;
			free(indicators[i].srect);
			indicators.erase(indicators.begin() + i);
			index = i;
			break ;
		}
	}
	while (index < indicators.size() && visited != true)
	{
		indicators[index].killMove += 1;
		index++;
	}
}

void TurnOrder::KillMoveUpdate()
{
	int iter = 0;
	int targ = 0;
	int posDiff = rounding(((float)gameCamera.screen.width / 23.2f));
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
		indicators[i].x -= (float)gameCamera.screen.width / 600.0f;
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
	if (turnStartActive)
		UpdateStartTurn();
	if (turnChange)
		ChangeTurn();
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
	if (killActive)
		KillMoveUpdate();
	CheckClickBox();
	MouseScroll();
	UpdateHoverIndicator();
}

void TurnOrder::Destroy()
{
	delete banner;
	delete backGround;
	delete hoverIndicator;
	for (int i = 0; i < indicators.size(); i++)
	{
		delete indicators[i].indicator;
		free(indicators[i].srect);
	}
	indicators.clear();
	characters.clear();
	gameState.updateObjs.turnOrder = NULL;
}
