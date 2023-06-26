
#ifndef SELECTOR_H
# define SELECTOR_H

# include "../ab.h"

class Selector
{
	private:
		int **map;
		void ClearPositionOutOfRange(int cleared, SDL_Point start);
		GroundColoring *groundColoring;
	public:
		Selector(SDL_Point start, int dist, int cleared, bool trees, GroundColoring *coloring);
		Character *Update();
		void Destroy();
};

#endif
