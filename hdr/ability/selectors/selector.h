
#ifndef SELECTOR_H
# define SELECTOR_H

# include "../../ab.h"

class Selector
{
	private:
		int **map;
		SDL_Point position;
		Sprite *block = NULL;
		bool trees = false;
		bool sForAlly = false;
		bool sForEnemy = true;
		bool stunEnemy = false;
		bool stunAlly = false;
		void ClearPositionOutOfRange(int cleared, SDL_Point start);
		Character *GetRet(Character *character, SDL_Point pos);
		GroundColoring *groundColoring;
		void SetBlock(SDL_Point target);
		void SetBlockSprite(SDL_Point pos);
		void BlockUpdater();
	public:
		Selector(SDL_Point start, int dist, int cleared, GroundColoring *coloring, bool staticSearch, bool trees);
		~Selector() {Destroy();};
		void SetSelectorFor(bool ally, bool enemy) {sForAlly = ally; sForEnemy = enemy;};
		void ClearStunned(bool ally, bool enemy) {stunAlly = ally; stunEnemy = enemy;};
		void IncludePoint(SDL_Point pos, int mark = 1);
		Character *Update();
		void Destroy();
};

#endif
