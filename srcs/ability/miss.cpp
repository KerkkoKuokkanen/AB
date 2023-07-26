
#include "../../hdr/global.h"

MISS *createBasicMISS(SDL_Point start, SDL_Point target, bool sound)
{
	Character *targ = gameState.battle.ground->map[target.y][target.x].character;
	if (targ == NULL)
		return NULL;
	if (targ->killed)
		return (NULL);
	bool left = false;
	SDL_Rect dest1 = gameState.battle.ground->getTileDest(start);
	SDL_Rect dest2 = gameState.battle.ground->getTileDest(target);
	if (dest1.x > dest2.x)
		left = true;
	Vector place((float)(dest2.x + 3000), (float)(dest2.y + 1700.0f));
	if (targ != NULL)
	{
		SDL_Rect dest = targ->sprite->dest;
		place.x = (float)(dest.x + (dest.w / 3));
		place.y = (float)(dest.y + (dest.h / 4));
	}
	return (new MISS(place, sound, left));
}

MISS::MISS(Vector place, bool sound, bool left)
{
	if (sound)
		PlaySound(gameState.audio.whiff, Channels::WHIFF, 0);
	SDL_Rect dest = {0, 0, 2200, 1100};
	miss = new Sprite(gameState.textures.MISS, dest, NULL, NULL, 0, FLIP_NONE);
	miss->Position(place);
	gameState.render->AddSprite(miss, MISS_LAYER);
	MISS::left = left;
	dirMulti = (left) ? (-1.0f) : 1.0f;
	direction = {35.0f, -90.0f};
	counter = 0;
}

void MISS::AlphaScale()
{
	if (counter > 40)
	{
		alpha -= 10;
		if (alpha < 0)
			alpha = 0;
		miss->AlphaMod(alpha);
	}
}

void MISS::MoveMiss()
{
	miss->Move(Vector(direction.x * dirMulti, direction.y));
	direction.x *= 1.01f;
	direction.y /= 1.01f;
}

void MISS::ScaleMiss()
{
	if (counter > 40)
		return ;
	SDL_Rect dest = miss->dest;
	dest.w += 30;
	dest.h += 20;
	dest.x -= 15;
	dest.y -= 10;
	miss->dest = dest;
}

void MISS::Update()
{
	if (alpha <= 0)
	{
		done = true;
		return ;
	}
	AlphaScale();
	MoveMiss();
	ScaleMiss();
	counter++;
}

void MISS::Destroy()
{
	delete miss;
}
