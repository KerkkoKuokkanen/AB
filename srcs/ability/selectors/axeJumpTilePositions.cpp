
#include "../../../hdr/global.h"

static int GetSecotr(SDL_Point target, SDL_Point character)
{
	if (character.y < target.y)
	{
		if (character.x == target.x && (character.y % 2) == (target.y % 2))
			return (1);
		int xLeft = getXToLeft(target);
		if (character.x <= xLeft)
			return (0);
		return (2);
	}
	if (character.x > target.x && character.y == target.y)
		return (3);
	if (character.y > target.y)
	{
		if (character.x == target.x && (character.y % 2) == (target.y % 2))
			return (5);
		int xRight = getXToRight(target);
		if (character.x >= xRight)
			return (4);
		return (6);
	}
	return (7);
}

static bool CheckPos(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	if (gameState.battle.ground->map[pos.y][pos.x].blocked)
		return (false);
	return (true);
}

void AxeJumpSelector::CreateTileSelector()
{
	SDL_Point targ = targetEnemy->position;
	int sector = GetSecotr(targ, start);
	int xLeft = getXToLeft(targ);
	int xRight = getXToRight(targ);
	posSelector = new TileSelector(targ, 1, 1, coloring, false, true);
	switch (sector)
	{
		case 0:
		{
			if (CheckPos({xLeft, targ.y + 1}))
				posSelector->IncludePoint({xLeft, targ.y + 1});
			if (CheckPos({xLeft, targ.y - 1}))
				posSelector->IncludePoint({xLeft, targ.y - 1});
			if (CheckPos({xRight, targ.y - 1}))
				posSelector->IncludePoint({xRight, targ.y - 1});
			break ;
		}
		case 1:
		{
			if (CheckPos({xLeft, targ.y - 1}))
				posSelector->IncludePoint({xLeft, targ.y - 1});
			if (CheckPos({xRight, targ.y - 1}))
				posSelector->IncludePoint({xRight, targ.y - 1});
			break ;
		}
		case 2:
		{
			if (CheckPos({xRight, targ.y + 1}))
				posSelector->IncludePoint({xRight, targ.y + 1});
			if (CheckPos({xRight, targ.y - 1}))
				posSelector->IncludePoint({xRight, targ.y - 1});
			if (CheckPos({xLeft, targ.y - 1}))
				posSelector->IncludePoint({xLeft, targ.y - 1});
			break ;
		}
		case 3:
		{
			if (CheckPos({xRight, targ.y - 1}))
				posSelector->IncludePoint({xRight, targ.y - 1});
			if (CheckPos({xRight, targ.y + 1}))
				posSelector->IncludePoint({xRight, targ.y + 1});
			break ;
		}
		case 4:
		{
			if (CheckPos({xRight, targ.y + 1}))
				posSelector->IncludePoint({xRight, targ.y + 1});
			if (CheckPos({xRight, targ.y - 1}))
				posSelector->IncludePoint({xRight, targ.y - 1});
			if (CheckPos({xLeft, targ.y + 1}))
				posSelector->IncludePoint({xLeft, targ.y + 1});
			break ;
		}
		case 5:
		{
			if (CheckPos({xLeft, targ.y + 1}))
				posSelector->IncludePoint({xLeft, targ.y + 1});
			if (CheckPos({xRight, targ.y + 1}))
				posSelector->IncludePoint({xRight, targ.y + 1});
			break ;
		}
		case 6:
		{
			if (CheckPos({xLeft, targ.y + 1}))
				posSelector->IncludePoint({xLeft, targ.y + 1});
			if (CheckPos({xLeft, targ.y - 1}))
				posSelector->IncludePoint({xLeft, targ.y - 1});
			if (CheckPos({xRight, targ.y + 1}))
				posSelector->IncludePoint({xRight, targ.y + 1});
			break ;
		}
		case 7:
		{
			if (CheckPos({xLeft, targ.y + 1}))
				posSelector->IncludePoint({xLeft, targ.y + 1});
			if (CheckPos({xLeft, targ.y - 1}))
				posSelector->IncludePoint({xLeft, targ.y - 1});
			break ;
		}
	}
}
