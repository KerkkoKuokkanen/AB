
#ifndef SELECTOR_FOR_TILES_H
# define SELECTOR_FOR_TILES_H

# include "../../ab.h"

class TileSelector
{
	private:
		int **map;
		void ClearPositionOutOfRange(int cleared, SDL_Point start);
		GroundColoring *groundColoring;
	public:
		TileSelector(SDL_Point start, int dist, int cleared, GroundColoring *coloring, bool blokers, bool staticSearch = false);
		~TileSelector() {Destroy();};
		void IncludePoint(SDL_Point pos, int mark = 1);
		SDL_Point Update();
		void Destroy();
};

#endif