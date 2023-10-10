
#ifndef AXE_JUMP_SELECTOR_H
# define AXE_JUMP_SELECTOR_H

# include "../../ab.h"

class AxeJumpSelector
{
	private:
		SDL_Point start;
		Character *targetEnemy = NULL;
		SDL_Point targetLandingPos = {-1, -1};
		Selector *enemySelector = NULL;
		TileSelector *posSelector = NULL;
		GroundColoring *coloring;
		void ClearSelectorPositions();
		void CreateTileSelector();
		void UpdateEnemySelector();
		void UpdateTileSelector();
	public:
		bool done = false;
		AxeJumpSelector(SDL_Point start, int range, GroundColoring *coloring);
		~AxeJumpSelector() {Destroy();};
		Character *GetTargetEnemy() {return (targetEnemy);};
		SDL_Point GetTargetLandingPos() {return (targetLandingPos);};
		void Update();
		void Destroy();
};

#endif
