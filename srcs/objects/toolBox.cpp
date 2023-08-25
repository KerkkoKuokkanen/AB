
#include "../../hdr/global.h"

ToolBox::ToolBox(Character *character)
{
	ToolBox::character = character;
	SDL_Rect dest = character->sprite->dest;
	sprite = new Sprite(gameState.textures.chars.handTools[1], dest, NULL, NULL, 0, FLIP_NONE);
	sprite->orderLayer = character->sprite->orderLayer;
	sprite->z = character->sprite->z + 0.05f;
	gameState.render->AddSprite(sprite, BATTLEGROUND_LAYER);
}

void ToolBox::UpdateToolBoxInHand()
{
	if (!inHand)
		return ;
	SDL_Rect dest = character->sprite->dest;
	float angle = character->sprite->getAngle();
	SDL_Texture *text = character->sprite->getTexture();
	if (text == gameState.textures.chars.smithIdle[0])
		sprite->setTexture(gameState.textures.chars.handTools[0]);
	else
		sprite->setTexture(gameState.textures.chars.handTools[1]);
	sprite->setAngle(angle);
	sprite->dest = dest;
	sprite->orderLayer = character->sprite->orderLayer;
	sprite->z = character->sprite->z + 0.05f;
	sprite->AlphaMod(character->sprite->getAlpha());
}

void ToolBox::Update()
{
	UpdateToolBoxInHand();
}
