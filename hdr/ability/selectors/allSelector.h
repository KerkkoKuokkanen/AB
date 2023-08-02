
#ifndef ALL_SELECTOR_H
# define ALL_SELECTOR_H

# include "../../ab.h"

class AllSelector
{
	public:
		AllSelector(SDL_Point start, int dist, int cleared, GroundColoring *coloring, bool staticSearch, bool trees);
};

#endif
