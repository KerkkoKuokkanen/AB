
#include "../../hdr/global.h"

void Character::CreateCharacterType(int skin)
{
	cSing = skin;
	switch (skin)
	{
		case 0:
		{
			SDL_Rect dest = {-3000, -450, 5800, 7500};
			textures.push_back(gameState.textures.thiefIdle1);
			textures.push_back(gameState.textures.thiefIdle2);
			stands.push_back(gameState.textures.stands.thiefIdle1Stand);
			stands.push_back(gameState.textures.stands.thiefIdle2Stand);
			sprite = new Sprite(gameState.textures.thiefIdle1, dest, NULL, NULL, 0, FLIP_NONE);
			stand = new Sprite(gameState.textures.stands.thiefIdle1Stand, dest, NULL, NULL, 0, FLIP_NONE);
			break ;
		}
		case 1:
		{
			SDL_Rect skele = {-3000, -450, 6500, 6500};
			textures.push_back(gameState.textures.skeleIdle1);
			textures.push_back(gameState.textures.skeleIdle2);
			stands.push_back(gameState.textures.stands.skeleIdle1Stand);
			stands.push_back(gameState.textures.stands.skeleIdle2Stand);
			sprite = new Sprite(gameState.textures.skeleIdle1, skele, NULL, NULL, 0, FLIP_NONE);
			stand = new Sprite(gameState.textures.stands.skeleIdle1Stand, skele, NULL, NULL, 0, FLIP_NONE);
			break ;
		}
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
	delete stand;
	delete this;
}

void Character::AddToRender()
{
	gameState.render->AddSprite(sprite, BATTLEGROUND_LAYER);
	gameState.render->AddSprite(stand, BATTLEGROUND_LAYER);
}

void Character::Update()
{
	if (killed)
	{
		clicked = false;
		return ;
	}
	if (stats.health <= 0)
		gameState.updateObjs.killer->AddCharacterToKill(this);
	if (gameState.keys.rightClick == 1 && gameState.keys.click != 1)
		clicked = false;
	if (animationActive)
		return ;
	if (gameState.updateObjs.characterAnimIter == 50)
	{
		currentTexture = (currentTexture == 0) ? 1 : 0;
		sprite->setTexture(textures[currentTexture]);
		stand->setTexture(stands[currentTexture]);
	}
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
	stand->Position(to);
};

void Character::Move(Vector amount)
{
	sprite->Move(amount);
	stand->Move(amount);
};

void Character::Destroy()
{
	delete sprite;
	delete stand;
	textures.clear();
	stands.clear();
}
