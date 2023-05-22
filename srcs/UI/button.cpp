
#include "../../hdr/global.h"

Button::Button(SDL_Texture *button, SDL_Rect dest, SDL_Rect clickBox)
{
	sprite = new Sprite(button, dest, NULL, NULL, 0, FLIP_NONE, true);
	sprite->setTranslation(false);
	gameState.render->AddSprite(sprite, TURN_ORDER_LAYER);
	Button::clickBox = clickBox;
}

bool Button::Update()
{
	if (!active)
		return (false);
	SDL_Point point = {gameState.keys.mouseX, gameState.keys.mouseY};
	bool ret = pointCheck(point, clickBox);
	sprite->ClearAlphaMod();
	if (ret)
		sprite->AlphaMod(125);
	if (ret && gameState.keys.click == RELEASE_CLICK)
		return (true);
	return (false);
}
