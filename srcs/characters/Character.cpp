
#include "../../hdr/global.h"

void Character::CreateCharacterType(int skin)
{
	cSing = skin;
	SDL_Rect dest = {-3000, -450, 5800, 7500};
	SDL_Rect skele = {-3000, -450, 6500, 6500};
	switch (skin)
	{
		case 0:
			textures.push_back(gameState.textures.thiefIdle1);
			textures.push_back(gameState.textures.thiefIdle2);
			sprite = new Sprite(gameState.textures.thiefIdle1, dest, NULL, NULL, 0, FLIP_NONE);
			break ;
		case 1:
			textures.push_back(gameState.textures.skeleIdle1);
			textures.push_back(gameState.textures.skeleIdle2);
			sprite = new Sprite(gameState.textures.skeleIdle1, skele, NULL, NULL, 0, FLIP_NONE);
			break ;
	}
}

Character::Character(int skin, bool allied)
{
	CreateCharacterType(skin);
	width = 5800;
	height = 7500;
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
	if (killed)
	{
		clicked = false;
		return ;
	}
	if (clicked)
	{
		gameState.updateObjs.killer->AddCharacterToKill(this);
	}
	if (idleCounter == 50)
	{
		idleCounter = 0;
		currentTexture = (currentTexture == 0) ? 1 : 0;
		sprite->setTexture(textures[currentTexture]);
	}
	if (gameState.keys.rightClick == 1 && gameState.keys.click != 1)
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
};

void Character::Move(Vector amount)
{
	sprite->Move(amount);
	int x = amount.x, y = amount.y;
	if (amount.x - x >= 0.5f)
		x += 1;
	if (amount.y - y >= 0.5f)
		y += 1;
};

void Character::Destroy()
{
	delete sprite;
	textures.clear();
}
