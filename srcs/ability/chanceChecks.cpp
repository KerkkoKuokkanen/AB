
#include "../../hdr/global.h"

static bool CheckIfOnTheLeft(SDL_Point og, SDL_Point compare)
{
	if (compare.y % 2 == 0 && compare.x <= og.x)
		return (true);
	if (compare.y % 2 == 1 && compare.x < og.x)
		return (true);
	return (false);
}

static bool CheckIfOnTheRight(SDL_Point og, SDL_Point compare)
{
	if (og.y % 2 == 0)
	{
		if (compare.x >= og.x)
			return (true);
		return (false);
	}
	if (compare.y % 2 == 0 && compare.x > og.x)
		return (true);
	if (compare.y % 2 == 1 && compare.x >= og.x)
		return (true);
	return (false);
}

void Abilities::SetBlockSprite(SDL_Point pos, int size)
{
	if (block != NULL)
		return ;
	Sprite *tile = gameState.battle.ground->GetSprite(pos);
	SDL_Rect dest = {tile->dest.x + 1340, tile->dest.y - 2300, 3150, 3150};
	block = new Sprite(gameState.textures.blocks[size], dest, NULL, NULL, 0, FLIP_NONE);
	gameState.render->AddSprite(block, DUST_LAYER);
}

void Abilities::SetBlockSpriteAndChance(SDL_Point pos)
{
	Character *character = NULL;
	Object *obj = NULL;
	if (gameState.battle.ground->map[pos.y][pos.x].obj != NULL)
		obj = gameState.battle.ground->map[pos.y][pos.x].obj;
	if (gameState.battle.ground->map[pos.y][pos.x].character != NULL)
		character = gameState.battle.ground->map[pos.y][pos.x].character;
	int size = 0;
	if (obj != NULL)
	{
		if (obj->size == 2)
			chance = 5;
		else if (obj->size == 1)
		{
			size = 1;
			chance = rounding((float)chance / HALF_BLOCK_CHANCE_REDUCE_AMOUNT);
		}
	}
	else
	{
		size = 1;
		chance = rounding((float)chance / HALF_BLOCK_CHANCE_REDUCE_AMOUNT);
		chance = rounding((float)chance / 4.0f);
	}
	SetBlockSprite(pos, size);
}

void Abilities::SetUpBlock(Character *target)
{
	int ret = CheckBlock(target);
	if (ret == 0)
	{
		if (block != NULL)
			delete block;
		block = NULL;
		return ;
	}
	SDL_Point tPos = gameState.updateObjs.indicator->FindCharacter(target);
	SDL_Point pos = {0, 0};
	switch (ret)
	{
		case 1:
			pos = {getXToLeft(tPos), tPos.y - 1};
			break ;
		case 2:
			pos = {getXToLeft(tPos), tPos.y + 1};
			break ;
		case 3:
			pos = {getXToRight(tPos), tPos.y + 1};
			break ;
		case 4:
			pos = {getXToRight(tPos), tPos.y - 1};
			break ;
	}
	SetBlockSpriteAndChance(pos);
}

void Abilities::ChanceFromStats(Character *target)
{
	SDL_Point cPos = gameState.updateObjs.indicator->FindCharacter(character);
	SDL_Point tPos = gameState.updateObjs.indicator->FindCharacter(target);
	int height = gameState.battle.ground->map[cPos.y][cPos.x].height - gameState.battle.ground->map[tPos.y][tPos.x].height;
	if (height > 3)
		height = 3;
	if (height < -3)
		height = -3;
	chance += 5 * height;
	return ;
}

void Abilities::GetChance(Character *target)
{
	if (chance >= 200)
		return ;
	ChanceFromStats(target);
	if (blocks)
		SetUpBlock(target);
	if (chance > 95)
		chance = 95;
}

Character *Abilities::FindBlocker()
{
	Character *ret = NULL;
	int square = CheckBlock(target);
	SDL_Point pos = {0, 0};
	SDL_Point tPos = gameState.updateObjs.indicator->FindCharacter(target);
	switch (square)
	{
		case 0:
			return (NULL);
		case 1:
			pos = {getXToLeft(tPos), tPos.y - 1};
			break ;
		case 2:
			pos = {getXToLeft(tPos), tPos.y + 1};
			break ;
		case 3:
			pos = {getXToRight(tPos), tPos.y + 1};
			break ;
		case 4:
			pos = {getXToRight(tPos), tPos.y - 1};
			break ;
	}
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (ret);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (ret);
	if (gameState.battle.ground->map[pos.y][pos.x].character != NULL)
		ret = gameState.battle.ground->map[pos.y][pos.x].character;
	return (ret);
}

void Abilities::RangedTargetCheck()
{
	Character *ret = FindBlocker();
	if (ret == NULL)
	{
		if (rand() % 100 < chance)
			chance = 1;
		else
			chance = 0;
		return ;
	}
	int hit = rand() % 100;
	if (hit < chance)
	{
		chance = 1;
		return ;
	}
	if (hit < rounding(chance * 3.0f + chance))
	{
		target = ret;
		chance = 1;
		return ;
	}
	chance = 0;
}

int Abilities::CheckBlock(Character *target)
{
	SDL_Point pos = gameState.updateObjs.indicator->FindCharacter(target);
	t_GMU *topLeft = getMapTopLeft(pos);
	t_GMU *topRight = getMapTopRight(pos);
	t_GMU *downLeft = getMapDownLeft(pos);
	t_GMU *downRight = getMapDownRight(pos);
	SDL_Point pPos = gameState.updateObjs.indicator->FindCharacter(character);
	SDL_Point tPos = {getXToLeft(pos), pos.y - 1};
	if (topLeft != NULL)
	{
		if ((topLeft->obj != NULL || topLeft->character != NULL) && CheckIfOnTheLeft(tPos, pPos) && pPos.y <= tPos.y)
			return (1);
	}
	tPos.y = pos.y + 1;
	if (downLeft != NULL)
	{
		if ((downLeft->obj != NULL || downLeft->character != NULL) && CheckIfOnTheLeft(tPos, pPos) && pPos.y >= tPos.y)
			return (2);
	}
	tPos.x = getXToRight(pos);
	if (downRight != NULL)
	{
		if ((downRight->obj != NULL || downRight->character != NULL) && CheckIfOnTheRight(tPos, pPos) && pPos.y >= tPos.y)
			return (3);
	}
	tPos.y = pos.y - 1;
	if (topRight != NULL)
	{
		if ((topRight->obj != NULL || topRight->character != NULL) && CheckIfOnTheRight(tPos, pPos) && pPos.y <= tPos.y)
			return (4);
	}
	return (0);
}
