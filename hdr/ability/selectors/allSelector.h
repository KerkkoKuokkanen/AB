
#ifndef ALL_SELECTOR_H
# define ALL_SELECTOR_H

# include "../../ab.h"

class AllSelector
{
	private:
		int **map = NULL;
		int statusSign;
		GroundColoring *coloring;
		void ClearPositionOutOfRange(int cleared, SDL_Point start);
		void UpdatePoints();
	public:
		bool done = false;
		AllSelector(SDL_Point start, int dist, int cleared, GroundColoring *coloring, bool staticSearch, int statusSign = (-1));
		~AllSelector() {Destroy();};
		std::vector<SDL_Point> getTargets();
		void IncludePoint(SDL_Point pos);
		void Update();
		void Destroy();
};

#endif
