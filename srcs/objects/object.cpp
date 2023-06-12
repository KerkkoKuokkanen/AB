
#include "../../hdr/global.h"

Object::Object(int type, SDL_Point position, bool fadeOnMouseOver)
{
	SDL_Rect dest = getRect(type, position);
	int objSize = getObjSize(type);
	pos = position;
	t_TextAndSur use = getTextureAndSurface(type);
	sur = use.sur;
	sprite = new Sprite(use.text, dest, NULL, NULL, 0, FLIP_NONE);
	gameState.render->AddSprite(sprite, BATTLEGROUND_LAYER);
	int height = gameState.battle.ground->map[position.y][position.x].height;
	gameState.battle.ground->map[position.y][position.x].blocked = true;
	gameState.battle.ground->map[position.y][position.x].objSize = objSize;
	size = objSize;
	sprite->orderLayer = (position.y + 1);
	sprite->setDepth(height * BATTLE_DEPTH_UNIT + 4);
	Object::fadeOnMouseOver = fadeOnMouseOver;
	overCounter = 0;
	gameState.updateObjs.objUpdate->AddObject(this);
}

void Object::CheckMouseHover()
{
	if (gameState.battle.ground->HoverOverCheck(pos) || gameState.updateObjs.hover.overAnythingButCharacter)
	{
		overCounter = 0;
		return ;
	}
	if (gameState.updateObjs.hover.overCharacter)
	{
		SDL_Point position;
		if (gameState.updateObjs.chosen != NULL)
			position = gameState.updateObjs.indicator->FindCharacter(gameState.updateObjs.chosen);
		else
		{
			overCounter = 0;
			return ;
		}
		if (position.y > pos.y)
		{
			overCounter = 0;
			return ;
		}
	}
	if (MenuHoverCheck(sur, sprite->dest, gameState.keys.mouseX, gameState.keys.mouseY))
	{
		if (overCounter < 10)
			overCounter++;
		else
			sprite->AlphaMod(35);
	}
	else
		overCounter = 0;
}

void Object::Update()
{
	sprite->ClearAlphaMod();
	if (fadeOnMouseOver)
		CheckMouseHover();
	if (gameState.battle.ground->map[pos.y][pos.x].active == false)
		sprite->AlphaMod(35);
	if (gameState.keys.shift != 0)
		sprite->AlphaMod(35);
}

t_TextAndSur Object::getTextureAndSurface(int type)
{
	t_TextAndSur ret = {NULL, NULL};
	switch (type)
	{
		case ObjectSigns::BUSH:
			ret.text = gameState.textures.trees[0];
			ret.sur = gameState.surfaces.trees[0];
			break ;
		case ObjectSigns::DEAD_TREE:
			ret.text = gameState.textures.trees[1];
			ret.sur = gameState.surfaces.trees[1];
			break ;
		case ObjectSigns::SMALL_TREE:
			ret.text = gameState.textures.trees[2];
			ret.sur = gameState.surfaces.trees[2];
			break ;
		case ObjectSigns::STUMP:
			ret.text = gameState.textures.trees[3];
			ret.sur = gameState.surfaces.trees[3];
			break ;
		case ObjectSigns::TREE:
			ret.text = gameState.textures.trees[4];
			ret.sur = gameState.surfaces.trees[4];
			break ;
		default :
			break ;
	}
	return (ret);
}

int Object::getObjSize(int type)
{
	int ret = 0;
	switch (type)
	{
		case ObjectSigns::BUSH:
			ret = 1;
			break ;
		case ObjectSigns::DEAD_TREE:
			ret = 2;
			break ;
		case ObjectSigns::SMALL_TREE:
			ret = 1;
			break ;
		case ObjectSigns::STUMP:
			ret = 1;
			break ;
		case ObjectSigns::TREE:
			ret = 2;
			break ;
		default :
			break ;
	}
	return (ret);
}

SDL_Rect Object::getRect(int type, SDL_Point position)
{
	SDL_Rect location = gameState.battle.ground->GetSprite(position)->dest;
	SDL_Rect ret = {0, 0, 0, 0};
	switch (type)
	{
		case ObjectSigns::BUSH:
			ret = {location.x - 1600, location.y - 7700, 10000, 11500};
			break ;
		case ObjectSigns::DEAD_TREE:
			ret = {location.x - 3500, location.y - 11600, 12000, 16000};
			break ;
		case ObjectSigns::SMALL_TREE:
			ret = {location.x - 3550, location.y - 11500, 13500, 16000};
			break ;
		case ObjectSigns::STUMP:
			ret = {location.x - 1200, location.y - 7200, 10000, 11500};
			break ;
		case ObjectSigns::TREE:
			ret = {location.x - 3500, location.y - 11600, 12000, 16000};
			break ;
		default :
			break ;
	}
	return (ret);
}
