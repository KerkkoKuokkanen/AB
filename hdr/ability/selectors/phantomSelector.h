
#ifndef PHANTOM_SELECTOR_H
# define PHANTOM_SELECTOR_H

# include "../../ab.h"

class PhantomSelector
{
	private:
		std::vector<SDL_Point> targets = {};
		std::vector<SDL_Point> additionals = {};
		Character *character;
		SDL_Point pos = {-1, -1};
		GroundColoring *coloring;
		TileSelector *selector = NULL;
		void HighlightAdditional(SDL_Point ret);
		void HighlightBlock(SDL_Point ret);
		bool CheckPoint(SDL_Point ret);
	public:
		bool done = false;
		PhantomSelector(Character *character, int range, GroundColoring *coloring, int cleared = 4);
		~PhantomSelector() {Destroy();};
		std::vector<SDL_Point> &GetTargets();
		void SetAdditionalHighlights(std::vector<SDL_Point> additionals);
		void SetDefaultAdditionals();
		void IncludePoint(SDL_Point pos) {selector->IncludePoint(pos);};
		void RemovePoint(SDL_Point pos) {selector->RemovePoint(pos);};
		void Update();
		void Destroy();
};

#endif
