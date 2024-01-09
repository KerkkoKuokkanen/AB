
#ifndef AI_ITERATOR_H
# define AI_ITERATOR_H

# include "../ab.h"

typedef struct s_BestMove
{
	float score;
	bool same;
}				t_BestMove;

class AiIterator
{
	private:
		t_AiMapUnit **map = NULL;
		t_AiCharacter character = {};
		float startScore = 0.0f;
		int depth = 0;
		t_BestMove action = {};
		void GetPossibleMoves();
		void IterateTheMap();
		void UseTheAbility(SDL_Point pos, t_Ability *ability, t_AiMapUnit **newMap);
		void HandleAbilityAction(SDL_Point pos, t_Ability *ability);
		void CheckForAbility(SDL_Point pos);
		void CheckForMove(SDL_Point pos);
	public:
		void CalculateMoves(t_AiMapUnit **map, t_AiCharacter character, float startScore, int depth);
		~AiIterator() {Destroy();};
		void Destroy();
};

#endif
