
#include "../../../hdr/global.h"

void SelectorQueue::AddNextSelector(bool normal, SDL_Point pos, int range, int cleared, bool blockers, bool staticSearch, bool (*compFunc)(SDL_Point, SDL_Point))
{
	t_Selec add = {normal, pos, range, cleared, blockers, staticSearch, compFunc, false, true};
	nextSelectors.push_back(add);
}

void SelectorQueue::AddNextSelectorWithTarget(bool normal, SDL_Point pos, int range, int cleared, bool blockers, bool staticSearch, bool ally, bool enemy, bool (*compFunc)(SDL_Point, SDL_Point))
{
	t_Selec add = {normal, pos, range, cleared, blockers, staticSearch, compFunc, ally, enemy};
	nextSelectors.push_back(add);
}

void SelectorQueue::CreateNextSelector()
{
	t_Selec data = nextSelectors[0];
	SDL_Point pos = data.pos;
	if (pos.x == (-1))
	{
		if (targets.size() == 0)
		{
			done = true;
			return ;
		}
		pos = targets[targets.size() - 1];
	}
	if (data.normal)
	{
		selector = new Selector(pos, data.range, data.cleared, coloring, data.staticSearch);
		selector->SetSelectorFor(data.ally, data.enemy);
		if (data.additionalCompFunction != NULL)
			selector->AddAdditionalCompareFunction(data.additionalCompFunction);
		nextSelectors.erase(nextSelectors.begin() + 0);
		return ;
	}
	tileSelector = new TileSelector(pos, data.range, data.cleared, coloring, data.blockers, data.staticSearch);
	nextSelectors.erase(nextSelectors.begin() + 0);
}

void SelectorQueue::UpdateTileSelector()
{
	SDL_Point ret = tileSelector->Update();
	if (ret.x != (-1) && ret.y != (-1))
	{
		if (gameState.keys.click == RELEASE_CLICK)
		{
			targets.push_back(ret);
			delete tileSelector;
			tileSelector = NULL;
		}
	}
}

void SelectorQueue::UpdateSelector()
{
	Character *ret = selector->Update();
	if (ret != NULL)
	{
		if (gameState.keys.click == RELEASE_CLICK)
		{
			targets.push_back(ret->position);
			delete selector;
			selector = NULL;
		}
	}
}

void SelectorQueue::Update()
{
	done = false;
	if (nextSelectors.size() == 0 && tileSelector == NULL && selector == NULL)
	{
		done = true;
		return ;
	}
	if (tileSelector == NULL && selector == NULL)
		CreateNextSelector();
	if (tileSelector != NULL)
		UpdateTileSelector();
	if (selector != NULL)
		UpdateSelector();
}

std::vector<SDL_Point> SelectorQueue::GetTargets()
{
	return (targets);
}

void SelectorQueue::Destroy()
{
	if (selector != NULL)
		delete selector;
	if (tileSelector != NULL)
		delete tileSelector;
	nextSelectors.clear();
	targets.clear();
}
