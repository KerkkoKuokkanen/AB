
#include "../../hdr/global.h"

#define ALPHA_AMOUNT 133

static int GetTop(SDL_Surface *sur)
{
	Uint32 *pixels = (Uint32*)sur->pixels;
	int yStop = 0;
	bool broke = false;
	for (int i = 0; i < sur->h; i++)
	{
		for (int j = 0; j < sur->w; j++)
		{
			if (pixels[(i * sur->w) + j] == 0)
				continue ;
			broke = true;
			yStop = i;
			break ;
		}
		if (broke)
			break ;
	}
	return (yStop);
}

static int GetBottom(SDL_Surface *sur)
{
	Uint32 *pixels = (Uint32*)sur->pixels;
	int yStop = 0;
	bool broke = false;
	for (int i = sur->h - 1; i >= 0; i--)
	{
		for (int j = 0; j < sur->w; j++)
		{
			if (pixels[(i * sur->w) + j] == 0)
				continue ;
			broke = true;
			yStop = i;
			break ;
		}
		if (broke)
			break ;
	}
	return (yStop);
}

static void GetDimentions(t_HealthColoringClass &add, Character *charac)
{
	switch (charac->cSing)
	{
		case THIEF:
		{
			add.top1 = GetTop(gameState.surfaces.thiefIdle1);
			add.top2 = GetTop(gameState.surfaces.thiefIdle2);
			add.bottom1 = GetBottom(gameState.surfaces.thiefIdle1);
			add.bottom2 = GetBottom(gameState.surfaces.thiefIdle2);
			return ;
		}
		case SKELE:
		{
			add.top1 = GetTop(gameState.surfaces.skeleIdle1);
			add.top2 = GetTop(gameState.surfaces.skeleIdle2);
			add.bottom1 = GetBottom(gameState.surfaces.skeleIdle1);
			add.bottom2 = GetBottom(gameState.surfaces.skeleIdle2);
			return ;
		}
		case PYRO:
		{
			add.top1 = GetTop(gameState.surfaces.pyroIdle1);
			add.top2 = GetTop(gameState.surfaces.pyroIdle2);
			add.bottom1 = GetBottom(gameState.surfaces.pyroIdle1);
			add.bottom2 = GetBottom(gameState.surfaces.pyroIdle2);
			return ;
		}
		case LION:
		{
			add.top1 = GetTop(gameState.surfaces.lionIdle1);
			add.top2 = GetTop(gameState.surfaces.lionIdle2);
			add.bottom1 = GetBottom(gameState.surfaces.lionIdle1);
			add.bottom2 = GetBottom(gameState.surfaces.lionIdle2);
			return ;
		}
		case SMITH:
		{
			add.top1 = GetTop(gameState.surfaces.smithIdle1);
			add.top2 = GetTop(gameState.surfaces.smithIdle2);
			add.bottom1 = GetBottom(gameState.surfaces.smithIdle1);
			add.bottom2 = GetBottom(gameState.surfaces.smithIdle2);
			return ;
		}
		case MAGE:
		{
			add.top1 = GetTop(gameState.surfaces.mageIdle1);
			add.top2 = GetTop(gameState.surfaces.mageIdle2);
			add.bottom1 = GetBottom(gameState.surfaces.mageIdle1);
			add.bottom2 = GetBottom(gameState.surfaces.mageIdle2);
			return ;
		}
		case RAIDER:
		{
			add.top1 = GetTop(gameState.surfaces.raiderIdle1);
			add.top2 = GetTop(gameState.surfaces.raiderIdle2);
			add.bottom1 = GetBottom(gameState.surfaces.raiderIdle1);
			add.bottom2 = GetBottom(gameState.surfaces.raiderIdle2);
			return ;
		}
	}
}

static bool alreadyIn(std::vector<t_HealthColoringClass> &classes, int cSing)
{
	for (int i = 0; i < classes.size(); i++)
	{
		if (classes[i].cSing == cSing)
			return (true);
	}
	return (false);
}

void HealthColoring::Init()
{
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *charac = gameState.battle.ground->characters[i].character;
		t_HealthColoring used;
		used.character = charac;
		used.sRect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
		SDL_Surface *sur = getSurface(charac);
		used.sRect->x = 0;
		used.sRect->y = 0;
		used.sRect->w = 0;
		used.sRect->h = 0;
		used.sprite = new Sprite(charac->sprite->getTexture(), charac->sprite->dest, used.sRect, NULL, 0, FLIP_NONE);
		used.sprite->orderLayer = charac->sprite->orderLayer;
		used.sprite->z = charac->sprite->z + 0.0001f;
		used.sprite->ColorMod(255, 0, 0);
		used.sprite->AlphaMod(ALPHA_AMOUNT);
		gameState.render->AddSprite(used.sprite, BATTLEGROUND_LAYER);
		characters.push_back(used);
		if (alreadyIn(classes, charac->cSing))
			continue ;
		t_HealthColoringClass add;
		add.cSing = charac->cSing;
		GetDimentions(add, charac);
		classes.push_back(add);
	}
}

bool HealthColoring::ShouldDeactivate(int index)
{
	if (gameState.updateObjs.abilities->active)
	{
		Character *ret = gameState.updateObjs.abilities->GetCharacter();
		if (ret == characters[index].character)
			return (true);
		ret->sprite->ClearColorMod();
	}
	Sprite *used = characters[index].character->sprite;
	if (used->red != 0 || used->green != 0 || used->blue != 0)
		return (true);
	if (characters[index].character->stats.health >= characters[index].character->stats.maxHealth)
		return (true);
	if (characters[index].character->moving)
		return (true);
	return (false);
}

bool HealthColoring::ShouldDestroy(int index)
{
	if (characters[index].character->killed)
		return (true);
	return (false);
}

void HealthColoring::DestroyUnit(int index)
{
	delete characters[index].sprite;
	free(characters[index].sRect);
	characters.erase(characters.begin() + index);
}

t_HealthColoringClass *HealthColoring::GetCharacterDimentions(int cSing)
{
	for (int i = 0; i < classes.size(); i++)
	{
		if (classes[i].cSing == cSing)
			return (&classes[i]);
	}
	printf("health coloring returned NULL\n");
	return (NULL);
}

static bool CharacterNotFound(std::vector<t_HealthColoring> characters, Character *character)
{
	for (int i = 0; i < characters.size(); i++)
	{
		if (characters[i].character == character)
			return (false);
	}
	return (true);
}

void HealthColoring::CreateNewCharacter(Character *character)
{
	t_HealthColoring used;
	used.character = character;
	used.sRect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	used.sRect->x = 0;
	used.sRect->y = 0;
	used.sRect->w = 0;
	used.sRect->h = 0;
	used.sprite = new Sprite(character->sprite->getTexture(), character->sprite->dest, used.sRect, NULL, 0, FLIP_NONE);
	used.sprite->orderLayer = character->sprite->orderLayer;
	used.sprite->z = character->sprite->z + 0.0001f;
	used.sprite->ColorMod(255, 0, 0);
	used.sprite->AlphaMod(ALPHA_AMOUNT);
	gameState.render->AddSprite(used.sprite, BATTLEGROUND_LAYER);
	characters.push_back(used);
}

void HealthColoring::CreateNewCharacterClass(Character *character)
{
	if (alreadyIn(classes, character->cSing))
		return ;
	t_HealthColoringClass add;
	add.cSing = character->cSing;
	GetDimentions(add, character);
	classes.push_back(add);
}

void HealthColoring::PollForNewCharacters()
{
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *ret = gameState.battle.ground->characters[i].character;
		if (ret->killed)
			continue ;
		if (CharacterNotFound(characters, ret))
		{
			CreateNewCharacter(ret);
			CreateNewCharacterClass(ret);
		}
	}
}

static int WhatTextureUsedFromCharacter(Character *character)
{
	if (character->currentTexture == 0)
		return (1);
	return (2);
}

static int GetSourceY(int health, int max, int top, int bottom)
{
	if (health < 0)
		health = 0;
	float scala = (float)(bottom - top);
	float precent = 1.0f - (float)health / (float)max;
	float addAmount = scala * precent;
	return (bottom - rounding(addAmount));
}

static SDL_Rect GetDest(SDL_Surface *sur, SDL_Rect dest, int y, int rest)
{
	float hUnit = (float)dest.h / (float)sur->h;
	float yAdd = hUnit * (float)y;
	dest.y += rounding(yAdd);
	float height = hUnit * rest;
	dest.h = rounding(height);
	return (dest);
}

void HealthColoring::UpdateUnit(int index)
{
	characters[index].sprite->Activate();
	Character *used = characters[index].character;
	characters[index].sprite->dest = used->sprite->dest;
	characters[index].sprite->orderLayer = used->sprite->orderLayer;
	characters[index].sprite->z = used->sprite->z + 0.0001f;
	characters[index].sprite->angle = used->sprite->angle;
	characters[index].sprite->setTexture(used->sprite->getTexture());
	t_HealthColoringClass *ret = GetCharacterDimentions(used->cSing);
	SDL_Surface *sur = getSurface(used);
	characters[index].sRect->w = sur->w - 1;
	int sourceY = GetSourceY(used->stats.health, used->stats.maxHealth, ret->top1, ret->bottom2);
	int rest = sur->h - sourceY;
	characters[index].sRect->h = rest;
	characters[index].sRect->y = sourceY;
	characters[index].sprite->dest = GetDest(sur, characters[index].character->sprite->dest, sourceY, rest);
}


void HealthColoring::Update()
{
	PollForNewCharacters();
	for (int i = 0; i < characters.size(); i++)
	{
		if (ShouldDestroy(i))
		{
			DestroyUnit(i);
			i = (characters.size() == 0) ? 0 : i - 1;
			continue ;
		}
		if (ShouldDeactivate(i))
		{
			characters[i].sprite->Deactivate();
			continue ;
		}
		UpdateUnit(i);
	}
}

void HealthColoring::Destroy()
{
	for (int i = 0; i < characters.size(); i++)
	{
		delete characters[i].sprite;
		free (characters[i].sRect);
	}
	characters.clear();
	classes.clear();
}
