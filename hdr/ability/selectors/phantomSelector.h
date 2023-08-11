
#ifndef PHANTOM_SELECTOR_H
# define PHANTOM_SELECTOR_H

# include "../../ab.h"

class PhantomSelector
{
	private:
		std::vector<SDL_Point> targets = {};
		int orientation = 0;
		Character *character;
		SDL_Point pos = {-1, -1};
		GroundColoring *coloring;
		TileSelector *selector = NULL;
		void HighlightAdditional(SDL_Point ret);
		void HighlightBlock(SDL_Point ret);
		bool CheckPoint(SDL_Point ret);
	public:
		bool done = false;
		PhantomSelector(Character *character, int range, GroundColoring *coloring);
		~PhantomSelector() {Destroy();};
		std::vector<SDL_Point> &GetTargets();
		void ChangeOrientation();
		void Update();
		void Destroy();
};

#endif
