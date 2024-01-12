
#ifndef AI_ITERATOR_H
# define AI_ITERATOR_H

# include "../ab.h"

typedef struct s_BestMove
{
	float score;
	bool same;
	SDL_Point pos;
	t_Ability *ability;
	t_AiCharacter *character;
}				t_BestMove;

class AiIterator
{
	private:
		t_AiMapUnit **map = NULL;
		t_AiCharacter character = {};
		float startScore = 0.0f;
		int depth = 0;
		t_BestMove action = {0.0f, true, {0, 0}, NULL, NULL};
		void GetPossibleMoves();
		void IterateTheMap();
		void SetAbilityToAction(SDL_Point pos, t_Ability *ability, t_AiMapUnit **newMap);
		void SetMoveToAction(SDL_Point pos, t_AiMapUnit **newMap);
		void UseTheAbility(SDL_Point pos, t_Ability *ability, t_AiMapUnit **newMap);
		void HandleAbilityAction(SDL_Point pos, t_Ability *ability);
		void CheckForAbility(SDL_Point pos);
		void CheckForMove(SDL_Point pos);
		int CheckMovePosition(SDL_Point pos);
		void HandleMoveAfterMath(SDL_Point target, int damage, int fatigue);
		void SetDefaultNoCharacter(SDL_Point pos, t_AiMapUnit **map);
		void SetDefaultCharacter(SDL_Point pos, t_AiCharacter *character, t_AiMapUnit **map);
	public:
		void CalculateMoves(t_AiMapUnit **map, t_AiCharacter character, float startScore, int depth);
		t_BestMove GetBestMove() {return(action);};
		~AiIterator() {Destroy();};
		void Destroy();
};

#endif
