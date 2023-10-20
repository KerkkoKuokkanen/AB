
#include "../../../hdr/global.h"

static int **GetAdditionals(Character *mage)
{
	t_Ability *thisOne = NULL;
	for (int i = 0; i < mage->abilities.size(); i++)
	{
		if (mage->abilities[i].type == HOST_EYES)
		{
			thisOne = &mage->abilities[i];
			break ;
		}
	}
	t_HostEyes *used = (t_HostEyes*)thisOne->stats;
	int range = used->hostRange;
	int **map = (int**)malloc(sizeof(int *) * gameState.battle.ground->map.size());
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
		map[i] = (int *)malloc(sizeof(int) * gameState.battle.ground->map[0].size());
	Character *ret = (Character*)mage->statuses.hosting;
	findMovables(map, range, ret->position);
	return (map);
}

void ExtendPhantSelector(Character *mage, PhantomSelector *selector)
{
	if (mage->statuses.hosting == NULL)
		return ;
	int **map = GetAdditionals(mage);
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (map[i][j] != TOOL_MAP_SIGN)
			{
				t_GMU &used = gameState.battle.ground->map[i][j];
				if (used.character != mage && used.additional.object == NULL &&
					used.obj == NULL)
					selector->IncludePoint({j, i});
			}
		}
	}
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
		free(map[i]);
	free(map);
}

PhantomSelector::PhantomSelector(Character *character, int range, GroundColoring *coloring, int cleared)
{
	PhantomSelector::character = character;
	PhantomSelector::coloring = coloring;
	selector = new TileSelector(character->position, range, cleared, coloring, false);
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (gameState.battle.ground->map[i][j].obj != NULL ||
				gameState.battle.ground->map[i][j].additional.object != NULL)
				selector->RemovePoint({j, i});
		}
	}
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
	for (int i = 0; i < additionals.size(); i++)
	{
		SDL_Point add = GetPositionFromCoordinates(ret, additionals[i]);
		HighlightBlock(add);
	}
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
	if (CheckPoint({x2, pos.y + 1}))
		targets.push_back({x2, pos.y + 1});
	if (CheckPoint({x2, pos.y - 1}))
		targets.push_back({x2, pos.y - 1});
	return (targets);
}

void PhantomSelector::SetAdditionalHighlights(std::vector<SDL_Point> additionals)
{
	for (int i = 0; i < additionals.size(); i++)
		PhantomSelector::additionals.push_back(additionals[i]);
}

void PhantomSelector::SetDefaultAdditionals()
{
	additionals = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
}

void PhantomSelector::Destroy()
{
	if (selector != NULL)
		delete selector;
}
