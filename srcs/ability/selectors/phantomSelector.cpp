
#include "../../../hdr/global.h"

static int getOrientation()
{
	static int orientation = 0;
	orientation = (orientation == 0) ? 1 : 0;
	return (orientation);
}

PhantomSelector::PhantomSelector(Character *character, int range, GroundColoring *coloring)
{
	PhantomSelector::character = character;
	PhantomSelector::coloring = coloring;
	orientation = getOrientation();
	selector = new TileSelector(character->position, range, 2, coloring, true, true);
	done = false;
}

void PhantomSelector::HighlightBlock(SDL_Point ret)
{
	if (ret.x < 0 || ret.x >= gameState.battle.ground->map[0].size())
		return ;
	if (ret.y < 0 || ret.y >= gameState.battle.ground->map.size())
		return ;
	if (gameState.battle.ground->map[ret.y][ret.x].character != NULL)
		return ;
	if (gameState.battle.ground->map[ret.y][ret.x].obj != NULL)
		return ;
	Color purp(84, 15, 20);
	coloring->SetColoredPosition(ret, purp, purp);
}

void PhantomSelector::HighlightAdditional(SDL_Point ret)
{
	if (ret.x == -1 || ret.y == -1)
		return ;
	int x1 = getXToRight(ret);
	int x2 = getXToLeft(ret);
	int y1 = (orientation == 0) ? (-1) : 1;
	int y2 = (orientation == 0) ? 1 : (-1);
	HighlightBlock({x1, ret.y + y1});
	HighlightBlock({x2, ret.y + y2});
}

void PhantomSelector::Update()
{
	if (done)
		return ;
	SDL_Point ret = selector->Update();
	HighlightAdditional(ret);
	if (ret.x != (-1) && ret.y != (-1) && gameState.keys.click == RELEASE_CLICK)
	{
		done = true;
		pos = ret;
	}
}

void PhantomSelector::Destroy()
{
	if (selector != NULL)
		delete selector;
}
