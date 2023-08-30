
#include "../../hdr/global.h"

static bool CheckValid(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	return (true);
}

int Object::GetTheHeightLeft()
{
	int left = getXToLeft(pos);
	int currH = gameState.battle.ground->map[pos.y][pos.x].height;
	SDL_Point pos1 = {left, pos.y + 1};
	int h1 = currH;
	if (CheckValid(pos1))
		h1 = gameState.battle.ground->map[pos1.y][pos1.x].height;
	if (h1 <= currH)
		return (h1);
	return (currH);
}

int Object::GetTheHeightRight()
{
	int right = getXToRight(pos);
	int currH = gameState.battle.ground->map[pos.y][pos.x].height;
	SDL_Point pos1 = {right, pos.y + 1};
	int h1 = currH;
	if (CheckValid(pos1))
		h1 = gameState.battle.ground->map[pos1.y][pos1.x].height;
	if (h1 <= currH)
		return (h1);
	return (currH);
}

Object::Object(int type, SDL_Point position, bool fadeOnMouseOver)
{
	SDL_Rect dest = getRect(type, position);
	size = getObjSize(type);
	pos = position;
	int use = getTextureAndSurface(type);
	surLeft = gameState.surfaces.treesLeft[use];
	surRight = gameState.surfaces.treesRight[use];
	spriteLeft = new Sprite(gameState.textures.treesLeft[use], dest, NULL, NULL, 0, FLIP_NONE);
	spriteRight = new Sprite(gameState.textures.treesRight[use], dest, NULL, NULL, 0, FLIP_NONE);
	gameState.render->AddSprite(spriteLeft, BATTLEGROUND_LAYER);
	gameState.render->AddSprite(spriteRight, BATTLEGROUND_LAYER);
	int height = gameState.battle.ground->map[position.y][position.x].height;
	gameState.battle.ground->map[position.y][position.x].blocked = true;
	gameState.battle.ground->map[position.y][position.x].obj = this;
	spriteLeft->orderLayer = (position.y + 1);
	spriteRight->orderLayer = (position.y + 1);
	int hLeft = GetTheHeightLeft();
	spriteLeft->setDepth(hLeft * BATTLE_DEPTH_UNIT + 0.1f);
	int hRight = GetTheHeightRight();
	spriteRight->setDepth(hRight * BATTLE_DEPTH_UNIT + 0.1f);
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
			position = gameState.updateObjs.chosen->position;
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
	if (MenuHoverCheck(surLeft, spriteLeft->dest, gameState.keys.mouseX, gameState.keys.mouseY) ||
		MenuHoverCheck(surRight, spriteRight->dest, gameState.keys.mouseX, gameState.keys.mouseY))
	{
		if (overCounter < 10)
			overCounter++;
		else
		{
			spriteLeft->AlphaMod(35);
			spriteRight->AlphaMod(35);
		}
	}
	else
		overCounter = 0;
}

void Object::Update()
{
	spriteLeft->ClearAlphaMod();
	spriteRight->ClearAlphaMod();
	if (fadeOnMouseOver)
		CheckMouseHover();
	if (gameState.battle.ground->map[pos.y][pos.x].active == false)
	{
		spriteLeft->AlphaMod(35);
		spriteRight->AlphaMod(35);
	}
	if (gameState.modes.filterMode == 1 || gameState.keys.control != 0)
	{
		spriteLeft->AlphaMod(35);
		spriteRight->AlphaMod(35);
	}
}

int Object::getTextureAndSurface(int type)
{
	switch (type)
	{
		case ObjectSigns::BUSH:
			return (0);
		case ObjectSigns::DEAD_TREE:
			return (1);
		case ObjectSigns::STUMP:
			return (2);
		case ObjectSigns::TREE:
			return (3);
		default :
			break ;
	}
	return (0);
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
