
#ifndef MULTI_SELECTOR_H
# define MULTI_SELECTOR_H

# include "../../ab.h"

class MultiSelector
{
	private:
		std::vector<SDL_Point> targets = {};
		std::vector<SDL_Point> included = {};
		Markers *markers = NULL;
		Selector *selector = NULL;
		GroundColoring *coloring;
		SDL_Point start;
		int distance;
		int cleared;
		int amount;
		bool trees;
		bool staticSearch;
		void CreateSelector();
		int count = 0;
	public:
		bool done = false;
		MultiSelector(SDL_Point start, int dist, int cleared, GroundColoring *coloring, bool staticSearch, bool trees, int selectAmount);
		~MultiSelector() {Destroy();};
		void IncludePoint(SDL_Point pos);
		void IncludePoints(std::vector<SDL_Point> &positions);
		std::vector<SDL_Point> &GetPositions();
		void Update();
		void Destroy();
};

#endif
