
#include "../../hdr/global.h"

Control::Control(SDL_Point pos, bool ally)
{
	Control::pos = pos;
	SDL_Rect place = gameState.battle.ground->getTileDest(pos);
	SDL_Rect dest = {place.x + 1650, place.y + 560, 2600, 1800};
	sprite = new Sprite(gameState.textures.control, dest, NULL, NULL, 0, FLIP_NONE);
	sprite->orderLayer = pos.y;
	int height = gameState.battle.ground->map[pos.y][pos.x].height;
	sprite->z = (float)height * (float)BATTLE_DEPTH_UNIT + 8.5f;
	gameState.render->AddSprite(sprite, BATTLEGROUND_LAYER);
	sprite->AlphaMod(170);
	if (!ally)
		sprite->ColorMod(82, 0, 4);
	else
		sprite->ColorMod(0, 77, 5);
}

void Control::Update()
{
	if (gameState.battle.ground->map[pos.y][pos.x].active == false)
		sprite->AlphaMod(10);
	else
	{
		sprite->AlphaMod(200);
	}
}

void Control::Destroy()
{
	if (sprite != NULL)
		delete sprite;
}
