
#include "../../hdr/global.h"

Character::Character(bool allied)
{
	textures.push_back(gameState.textures.thiefIdle1);
	textures.push_back(gameState.textures.thiefIdle2);
	SDL_Rect dest = {-3000, -450, 5800, 7500};
	sprite = new Sprite(gameState.textures.thiefIdle1, dest, NULL, NULL, 0, FLIP_NONE);
	width = 5800;
	height = 7500;
	clickBox.w = 3600;
	clickBox.h = 6500;
	if (!allied)
		ally = false;
}

void Character::DeleteCharacter()
{
	delete sprite;
	delete this;
}

void Character::AddToRender()
{
	gameState.render->AddSprite(sprite, 0);
}

void Character::Update()
{
	if (idleCounter == 50)
	{
		idleCounter = 0;
		currentTexture = (currentTexture == 0) ? 1 : 0;
		sprite->setTexture(textures[currentTexture]);
	}
	SDL_Point point = {gameState.keys.mouseX, gameState.keys.mouseY};
	hover = pointCheck(point, clickBox);
	if (hover && gameState.keys.click == 1)
		clicked = true;
	if (gameState.keys.rightClick == 1)
		clicked = false;
	idleCounter++;
}

void Character::setCoord(SDL_Point &coord)
{
	Character::coord = coord;
}

SDL_Point &Character::getCoord()
{
	return (coord);
}

void Character::Position(Vector to)
{
	sprite->Position(to);
	int x = to.x, y = to.y;
	if (to.x - x >= 0.5f)
		x += 1;
	if (to.y - y >= 0.5f)
		y += 1;
	clickBox.x = x + 1100;
	clickBox.y = y + 1050;
};

void Character::Move(Vector amount)
{
	sprite->Move(amount);
	int x = amount.x, y = amount.y;
	if (amount.x - x >= 0.5f)
		x += 1;
	if (amount.y - y >= 0.5f)
		y += 1;
	clickBox.x += x;
	clickBox.y += y;
};
