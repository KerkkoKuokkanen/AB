
#include "../../hdr/global.h"

Character::Character()
{
	textures.push_back(gameState.textures.thiefIdle1);
	textures.push_back(gameState.textures.thiefIdle2);
	SDL_Rect dest = {-3000, -450, 5800, 7500};
	sprite = new Sprite(gameState.textures.thiefIdle1, dest, NULL, NULL, 0, FLIP_NONE);
	width = 5800;
	height = 7500;
}

void Character::DeleteCharacter()
{
	delete sprite;
	delete this;
}

void Character::AddToRender()
{
	gameState.render->AddSprite(sprite, 1);
}

void Character::Update()
{
	if (idleCounter == 50)
	{
		idleCounter = 0;
		currentTexture = (currentTexture == 0) ? 1 : 0;
		sprite->setTexture(textures[currentTexture]);
	}
	idleCounter++;
}
