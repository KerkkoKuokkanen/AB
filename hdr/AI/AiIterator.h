
#ifndef AI_ITERATOR_H
# define AI_ITERATOR_H

# include "../ab.h"

typedef struct s_BestMove
{
	float score;

}				t_BestMove;

class AiIterator
{
	private:
		t_AiMapUnit **map = NULL;
		t_AiCharacter character = {};
		float startScore = 0.0f;
		int depth = 0;
		t_BestMove action = {0.0f};
		void GetPossibleMoves();
		void CalculateAbilityScores();
		void CheckDefaultAbilities();
		void SendToTargeting(t_Ability *ability);
	public:
		void CalculateMoves(t_AiMapUnit **map, t_AiCharacter character, float startScore, int depth);
		~AiIterator() {Destroy();};
		void Destroy();
};

#endif
