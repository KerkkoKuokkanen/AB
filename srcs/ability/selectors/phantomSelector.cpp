
#include "../../../hdr/global.h"

static int selectorOrientation = 0;

static int getOrientation()
{
	return (selectorOrientation);
}

void PhantomSelector::ChangeOrientation()
{
	orientation = (orientation == 0) ? 1 : 0;
	selectorOrientation = orientation;
}

PhantomSelector::PhantomSelector(Character *character, int range, GroundColoring *coloring)
{
	PhantomSelector::character = character;
	PhantomSelector::coloring = coloring;
	orientation = getOrientation();
	selector = new TileSelector(character->position, range, 4, coloring, false, true);
	done = false;
}

void PhantomSelector::HighlightBlock(SDL_Point ret)
{
	if (ret.x < 0 || ret.x >= gameState.battle.ground->map[0].size())
		return ;
	if (ret.y < 0 || ret.y >= gameState.battle.ground->map.size())
		return ;
	if (gameState.battle.ground->map[ret.y][ret.x].obj != NULL)
		return ;
	if (gameState.battle.ground->map[ret.y][ret.x].additional.object != NULL &&
		gameState.battle.ground->map[ret.y][ret.x].additional.type == AdditionalObjects::TOOLBOX)
		return ;
	Color purp(84, 15, 20);
	coloring->SetColoredPosition(ret, purp, purp);
}

bool PhantomSelector::CheckPoint(SDL_Point ret)
{
	if (ret.x < 0 || ret.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (ret.y < 0 || ret.y >= gameState.battle.ground->map.size())
		return (false);
	if (gameState.battle.ground->map[ret.y][ret.x].obj != NULL)
		return (false);
	if (gameState.battle.ground->map[ret.y][ret.x].additional.object != NULL &&
		gameState.battle.ground->map[ret.y][ret.x].additional.type == AdditionalObjects::TOOLBOX)
		return (false);
	return (true);
}

void PhantomSelector::HighlightAdditional(SDL_Point ret)
{
	if (ret.x == -1 || ret.y == -1)
		return ;
	int x1 = getXToRight(ret);
	int x2 = getXToLeft(ret);
	HighlightBlock({x1, ret.y + 1});
	HighlightBlock({x1, ret.y - 1});
	HighlightBlock({x2, ret.y + 1});
	HighlightBlock({x2, ret.y - 1});
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

std::vector<SDL_Point> &PhantomSelector::GetTargets()
{
	if (pos.x == -1)
		return (targets);
	int x1 = getXToRight(pos);
	int x2 = getXToLeft(pos);
	targets.push_back(pos);
	if (CheckPoint({x1, pos.y + 1}))
		targets.push_back({x1, pos.y + 1});
	if (CheckPoint({x1, pos.y - 1}))
		targets.push_back({x1, pos.y - 1});
	if (CheckPoint({x1, pos.y + 1}))
		targets.push_back({x2, pos.y + 1});
	if (CheckPoint({x1, pos.y - 1}))
		targets.push_back({x2, pos.y - 1});
	return (targets);
}

void PhantomSelector::Destroy()
{
	if (selector != NULL)
		delete selector;
}
