
#ifndef AI_ITERATOR_H
# define AI_ITERATOR_H

# include "../ab.h"

class AiIterator
{
	private:
		t_AiMapUnit **map = NULL;
		t_AiCharacter character = {};
		float startScore = 0.0f;
		int depth = 0;
		std::vector<SDL_Point> possibleMoves = {};
		bool passTested = false;
		void GetPossibleMoves();
	public:
		void CalculateMoves(t_AiMapUnit **map, t_AiCharacter character, float startScore, int depth);
		~AiIterator() {Destroy();};
		void Destroy();
};

#endif
