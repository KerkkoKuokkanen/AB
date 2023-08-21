
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

int RangedChance(Character *character, Character *target)
{
	SDL_Point cPos = character->position;
	SDL_Point tPos = target->position;
	int height = gameState.battle.ground->map[cPos.y][cPos.x].height - gameState.battle.ground->map[tPos.y][tPos.x].height;
	if (height > 3)
		height = 3;
	if (height < -3)
		height = -3;
	return (5 * height);
}

SDL_Point BlockPosition(SDL_Point cPos, SDL_Point tPos)
{
	int ret = CheckIfBlock(cPos, tPos);
	if (ret == 0)
		return {-1, -1};
	SDL_Point pos = tPos;
	switch (ret)
	{
		case 1:
			pos.x = getXToLeft(tPos); pos.y -= 1;
			break ;
		case 2:
			pos.x = getXToLeft(tPos); pos.y += 1;
			break ;
		case 3:
			pos.x = getXToRight(tPos); pos.y += 1;
			break ;
		case 4:
			pos.x = getXToRight(tPos); pos.y -= 1;
			break ;
	}
	return (pos);
}

void ChanceFromBlockers(int &chance, Character *character, Character *target)
{
	SDL_Point cPos = character->position;
	SDL_Point tPos = target->position;
	SDL_Point pos = BlockPosition(cPos, tPos);
	if (pos.x == (-1))
		return ;
	if (gameState.battle.ground->map[pos.y][pos.x].obj == NULL)
	{
		if (gameState.battle.ground->map[pos.y][pos.x].character == character
			|| gameState.battle.ground->map[pos.y][pos.x].character->killed)
			return ;
		chance = rounding((float)chance / HALF_BLOCK_CHANCE_REDUCE_AMOUNT);
		chance = rounding((float)chance / 4.0f);
		return ;
	}
	if (gameState.battle.ground->map[pos.y][pos.x].obj->size == 2)
	{
		chance = 5;
		return ;
	}
	chance = rounding((float)chance / HALF_BLOCK_CHANCE_REDUCE_AMOUNT);
}

int GetChance(Character *character, Character *target, t_Ability *ability)
{
	if (ability == NULL)
		return (0);
	if (ability->baseChance >= 200)
		return (200);
	int ret = ability->baseChance;
	switch (ability->type)
	{
		case DAGGER_THROW:
			ret += RangedChance(character, target);
			ChanceFromBlockers(ret, character, target);
			break ;
		case FLAME_BLAST:
			ret += RangedChance(character, target);
			ChanceFromBlockers(ret, character, target);
			break ;
		case DAGGER_SLASH:
			ret += RangedChance(character, target);
			break ;
	}
	if (ret > 95)
		ret = 95;
	if (ret < 5)
		ret = 5;
	return (ret);
}

Character *BasicCheck(Character *target, int &chance)
{
	if ((rand() % 100) < chance)
		chance = 1;
	else
		chance = 0;
	return (target);
}

bool MeleeCheck(Character *character, Character *target, t_Ability *ability)
{
	int chance = GetChance(character, target, ability);
	if (rand() % 100 < chance)
		return (true);
	return (false);
}

bool RangeCheckWithoutBlockers(Character *character, Character *target, t_Ability *ability)
{
	int chance = GetChance(character, target, ability);
	if (rand() % 100 < chance)
		return (true);
	return (false);
}

Character *RangedCheck(Character *character, Character *target, int &chance)
{
	SDL_Point cPos = character->position;
	SDL_Point tPos = target->position;
	SDL_Point pos = BlockPosition(cPos, tPos);
	if (pos.x == (-1))
		return (BasicCheck(target, chance));
	Character *ret = gameState.battle.ground->map[pos.y][pos.x].character;
	if (ret == NULL || ret == character)
		return (BasicCheck(target, chance));
	int hit = rand() % 100;
	int glit = rounding(chance * 3.0f + chance);
	if (hit < chance)
	{
		chance = 1;
		return (target);
	}
	if (hit < glit)
	{
		chance = 1;
		return (ret);
	}
	chance = 0;
	return (target);
}

int CheckIfBlock(SDL_Point characterPos, SDL_Point targetPos)
{
	SDL_Point pos = targetPos;
	t_GMU *topLeft = getMapTopLeft(pos);
	t_GMU *topRight = getMapTopRight(pos);
	t_GMU *downLeft = getMapDownLeft(pos);
	t_GMU *downRight = getMapDownRight(pos);
	SDL_Point pPos = characterPos;
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

bool StatusApply(t_Ability *ability, Character *character, Character *target)
{
	if (ability == NULL)
		return (false);
	if (ability->statusSign == (-1))
		return (false);
	int chance = 0;
	switch (ability->statType)
	{
		case StatStructs::ATTACK_AND_DEBUFF:
			t_AttackWithDebuff *used = (t_AttackWithDebuff*)ability->stats;
			chance = used->debuffChance;
			break ;
	}
	int hit = rand() % 100;
	if (hit < chance)
		return (true);
	return (false);
}
