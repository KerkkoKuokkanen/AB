
#include "../../hdr/global.h"

Button::Button(SDL_Texture *button, SDL_Rect dest, SDL_Rect clickBox)
{
	sprite = new Sprite(button, dest, NULL, NULL, 0, FLIP_NONE, true);
	gameState.render->AddSprite(sprite, INFO_LAYER);
	SDL_FRect box = staitcTranslateSprite(clickBox);
	Button::clickBox = {(int)box.x, (int)box.y, (int)box.w, (int)box.h};
}

void Button::SetClickBox(SDL_Rect clickBox)
{
	SDL_FRect box = staitcTranslateSprite(clickBox);
	Button::clickBox = {(int)box.x, (int)box.y, (int)box.w, (int)box.h};
}

int Button::Update()
{
	if (!active)
		return (NO_CONTACT);
	SDL_Point point = {gameState.keys.staticMouseX, gameState.keys.staticMouseY};
	bool ret = pointCheck(point, clickBox);
	sprite->ClearColorMod();
	if (ret)
	{
		sprite->ColorMod(180, 180, 180);
		if (gameState.keys.click == HOLD_CLICK)
			sprite->ColorMod(140, 140, 140);
	}
	if (ret && gameState.keys.click == RELEASE_CLICK)
		return (BUTTON_PRESS);
	if (ret)
		return (BUTTON_HOVER);
	return (NO_CONTACT);
}
