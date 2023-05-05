
#include "../../../hdr/global.h"

bool compareObjects(const t_Indicator &obj1, const t_Indicator &obj2) {
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

void TurnOrder::CreateIndicators()
{
	for (int i = 0; i < characters.size(); i++)
	{
		SDL_Rect *srect = (SDL_Rect*)malloc(sizeof(SDL_Rect) * 1);
		CreateSRect(srect, characters[i]->cSing);
		srects.push_back(srect);
		SDL_Rect dest = CreateDest(characters[i]->cSing);
		indicators.push_back({new Sprite(characters[i]->sprite->getTexture(), dest, srect, NULL, 0, FLIP_NONE, true),
																								characters[i], false});
		indicators[i].indicator->setTranslation(false);
		indicators[i].indicator->orderLayer = 1;
		gameState.render->AddSprite(indicators[i].indicator, TURN_ORDER_LAYER);
	}
}

TurnOrder::TurnOrder(std::vector<Character> &characters)
{
	for (int i = 0; i < characters.size(); i++)
		TurnOrder::characters.push_back(&characters[i]);
	SDL_Rect dest = {
		gameState.screen.width - (gameState.screen.width / 10 * 7),
		0 - (gameState.screen.height / 25),
		gameState.screen.width / 10 * 4,
		gameState.screen.height / 6
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
	CreateIndicators();
	StartTurn(); // this is temporarily here
}

void TurnOrder::StartTurn()
{
	std::sort(indicators.begin(), indicators.end(), compareObjects);
	for (int i = 0; i < indicators.size(); i++)
		indicators[i].active = true;
	int posDiff = rounding(((float)gameState.screen.width / 23.2f));
	for (int i = 0; i < indicators.size() && i < posCount; i++)
	{
		Vector place(
			(float)(indicators[i].indicator->dest.x + (posDiff * i)),
			(float)(indicators[i].indicator->dest.y)
		);
		indicators[i].indicator->Position(place);
	}
}

void TurnOrder::Update()
{
	
}

void TurnOrder::Destroy()
{
	delete banner;
	delete backGround;
	srects.clear();
	for (int i = 0; i < indicators.size(); i++)
		free(indicators[i].indicator);
	indicators.clear();
	characters.clear();
	gameState.updateObjs.turnOrder = NULL;
}
