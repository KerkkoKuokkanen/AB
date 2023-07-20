
#include "../../../hdr/global.h"

MultiSelector::MultiSelector(SDL_Point start, int dist, int cleared, GroundColoring *coloring, bool staticSearch, bool trees, int selectAmount)
{
	MultiSelector::start = start;
	distance = dist;
	MultiSelector::cleared = cleared;
	MultiSelector::coloring = coloring;
	MultiSelector::staticSearch = staticSearch;
	MultiSelector::trees = trees;
	amount = selectAmount;
	selector = NULL;
	markers = new Markers;
	CreateSelector();
}

void MultiSelector::CreateSelector()
{
	if (selector != NULL)
		delete selector;
	selector = new Selector(start, distance, cleared, coloring, staticSearch, trees);
}

void MultiSelector::Update()
{
	if (done)
		return ;
	Character *ret = selector->Update();
	if (ret != NULL)
	{
		if (gameState.keys.click == RELEASE_CLICK)
		{
			targets.push_back(ret->position);
			delete selector;
			selector = NULL;
			count++;
			markers->PlaceMarker(ret->position);
			if (count >= amount)
			{
				done = true;
				return ;
			}
			CreateSelector();
		}
	}
}

std::vector<SDL_Point> &MultiSelector::GetPositions()
{
	return (targets);
}

void MultiSelector::IncludePoints(std::vector<SDL_Point> &positions)
{
	for (int i = 0; i < positions.size(); i++)
		included.push_back(positions[i]);
}

void MultiSelector::IncludePoint(SDL_Point pos)
{
	included.push_back(pos);
}

void MultiSelector::Destroy()
{
	targets.clear();
	if (selector != NULL)
		delete selector;
	if (markers != NULL)
		delete markers;
}
