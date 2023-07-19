
#include "../../hdr/global.h"

void Character::AssignAbilities()
{
	switch (cSing)
	{
		case THIEF:
			abilities = {{DAGGER_THROW, 0, 80, NULL}, {SMOKE_BOMB, 0, 200, NULL}, {DAGGER_SLASH, 0, 80, NULL}};
			break ;
		case SKELE:
			break ;
		case PYRO:
			abilities = {{FLAME_PORT, 0, 200, NULL}, {FLAME_SLASH, 0, 80, NULL}};
			break ;
	}
}

void Character::CreateCharacterType(int skin)
{
	cSing = skin;
	switch (skin)
	{
		case THIEF:
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
		case SKELE:
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
		case PYRO:
		{
			SDL_Rect dest = {-3000, -450, 6800, 8160};
			textures.push_back(gameState.textures.chars.pyroIdle1);
			textures.push_back(gameState.textures.chars.pyroIdle2);
			stands.push_back(gameState.textures.stands.pyroStand);
			stands.push_back(gameState.textures.stands.pyroStand);
			sprite = new Sprite(gameState.textures.chars.pyroIdle1, dest, NULL, NULL, 0, FLIP_NONE);
			stand = new Sprite(gameState.textures.stands.pyroStand, dest, NULL, NULL, 0, FLIP_NONE);
			break ;
		}
	}
}
