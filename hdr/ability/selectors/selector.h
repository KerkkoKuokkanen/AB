
#ifndef SELECTOR_H
# define SELECTOR_H

# include "../../ab.h"

class Selector
{
	private:
		bool (*additionalCompFunction)(SDL_Point, SDL_Point) = NULL;
		int **map;
		SDL_Point position;
		bool sForAlly = false;
		bool sForEnemy = true;
		bool stunEnemy = false;
		bool stunAlly = false;
		void ClearPositionOutOfRange(int cleared, SDL_Point start);
		Character *GetRet(Character *character, SDL_Point pos);
		GroundColoring *groundColoring;
	public:
		Selector(SDL_Point start, int dist, int cleared, GroundColoring *coloring, bool staticSearch);
		~Selector() {Destroy();};
		void SetSelectorFor(bool ally, bool enemy) {sForAlly = ally; sForEnemy = enemy;};
		void ClearStunned(bool ally, bool enemy) {stunAlly = ally; stunEnemy = enemy;};
		void IncludePoint(SDL_Point pos, int mark = 1);
		void RemovePoint(SDL_Point pos);
		void AddAdditionalCompareFunction(bool (*compareFunction)(SDL_Point, SDL_Point)) {additionalCompFunction = compareFunction;};
		Character *Update();
		void Destroy();
};

#endif
