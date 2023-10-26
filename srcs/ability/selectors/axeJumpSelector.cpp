
#include "../../../hdr/global.h"

static int GetSecotr(SDL_Point target, SDL_Point character)
{
	if (character.y < target.y)
	{
		int xLeft = getXToLeft(target);
		if (character.x <= xLeft)
			return (0);
		if (character.x == target.x)
			return (1);
		return (2);
	}
	if (character.x > target.x && character.y == target.y)
		return (3);
	if (character.y > target.y)
	{
		int xRight = getXToRight(target);
		if (character.x >= xRight)
			return (4);
		if (character.x == target.x)
			return (5);
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

bool CompareFunction(SDL_Point start, SDL_Point target)
{
	int secotor = GetSecotr(target, start);
	int xLeft = getXToLeft(target);
	int xRight = getXToRight(target);
	switch (secotor)
	{
		case 0:
			if (CheckPos({xLeft, target.y + 1}) || CheckPos({xLeft, target.y - 1}) || CheckPos({xRight, target.y - 1}))
				return (true);
			break ;
		case 1:
			if (CheckPos({xLeft, target.y - 1}) || CheckPos({xRight, target.y - 1}))
				return (true);
			break ;
		case 2:
			if (CheckPos({xRight, target.y + 1}) || CheckPos({xRight, target.y - 1}) || CheckPos({xLeft, target.y - 1}))
				return (true);
			break ;
		case 3:
			if (CheckPos({xRight, target.y - 1}) || CheckPos({xRight, target.y + 1}))
				return (true);
			break ;
		case 4:
			if (CheckPos({xRight, target.y + 1}) || CheckPos({xRight, target.y - 1}) || CheckPos({xLeft, target.y + 1}))
				return (true);
			break ;
		case 5:
			if (CheckPos({xLeft, target.y + 1}) || CheckPos({xRight, target.y + 1}))
				return (true);
			break ;
		case 6:
			if (CheckPos({xLeft, target.y + 1}) || CheckPos({xLeft, target.y - 1}) || CheckPos({xRight, target.y + 1}))
				return (true);
			break ;
		case 7:
			if (CheckPos({xLeft, target.y + 1}) || CheckPos({xLeft, target.y - 1}))
				return (true);
			break ;
	}
	return (false);
}

void AxeJumpSelector::ClearSelectorPositions()
{
	SDL_Point used = {start.x + 1, start.y};
	enemySelector->RemovePoint(used);
	used = {start.x - 1, start.y};
	enemySelector->RemovePoint(used);
	used = {start.x, start.y - 2};
	enemySelector->RemovePoint(used);
	used = {start.x, start.y + 2};
	enemySelector->RemovePoint(used);
}

AxeJumpSelector::AxeJumpSelector(SDL_Point start, int range, GroundColoring *coloring)
{
	AxeJumpSelector::start = start;
	AxeJumpSelector::coloring = coloring;
	enemySelector = new Selector(start, range, 2, coloring, false);
	ClearSelectorPositions();
	enemySelector->AddAdditionalCompareFunction(&CompareFunction);
}

void AxeJumpSelector::UpdateEnemySelector()
{
	if (enemySelector == NULL)
		return ;
	Character *ret = enemySelector->Update();
	if (ret != NULL && gameState.keys.click == RELEASE_CLICK)
	{
		targetEnemy = ret;
		delete enemySelector;
		enemySelector = NULL;
		CreateTileSelector();
	}
}

void AxeJumpSelector::UpdateTileSelector()
{
	if (posSelector == NULL)
		return ;
	SDL_Point ret = posSelector->Update();
	if (ret.x != (-1) && ret.y != (-1) && gameState.keys.click == RELEASE_CLICK)
	{
		targetLandingPos = ret;
		done = true;
		delete posSelector;
		posSelector = NULL;
	}
}

void AxeJumpSelector::Update()
{
	if (done)
		return ;
	UpdateEnemySelector();
	UpdateTileSelector();
}

void AxeJumpSelector::Destroy()
{
	if (enemySelector != NULL)
		delete enemySelector;
	if (posSelector != NULL)
		delete posSelector;
}
