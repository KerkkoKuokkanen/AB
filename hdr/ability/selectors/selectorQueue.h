
#ifndef SELECTOR_QUEUE_H
# define SELECTOR_QUEUE_H

# include "../../ab.h"

typedef struct s_Selec
{
	bool normal;
	SDL_Point pos;
	int range;
	int cleared;
	bool blockers;
	bool staticSearch;
	bool (*additionalCompFunction)(SDL_Point, SDL_Point);
	bool ally;
	bool enemy;
}				t_Selec;

class SelectorQueue
{
	private:
		Selector *selector = NULL;
		TileSelector *tileSelector = NULL;
		std::vector<t_Selec> nextSelectors = {};
		std::vector<SDL_Point> targets = {};
		GroundColoring *coloring;
		void CreateNextSelector();
		void UpdateSelector();
		void UpdateTileSelector();
	public:
		bool done = false;
		SelectorQueue(GroundColoring *coloring, TileSelector *selec = NULL) {SelectorQueue::coloring = coloring; tileSelector = selec;};
		~SelectorQueue() {Destroy();};
		std::vector<SDL_Point> GetTargets();
		void AddStartingSelecotr(Selector *selector) {SelectorQueue::selector = selector;};
		void AddNextSelector(bool normal, SDL_Point pos, int range, int cleared, bool blockers, bool staticSearch, bool (*compFunc)(SDL_Point, SDL_Point) = NULL);
		void AddNextSelectorWithTarget(bool normal, SDL_Point pos, int range, int cleared, bool blockers, bool staticSearch, bool ally, bool enemy, bool (*compFunc)(SDL_Point, SDL_Point) = NULL);
		void Update();
		void Destroy();
};

#endif
