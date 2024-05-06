
#ifndef AI_ITERATOR_H
# define AI_ITERATOR_H

# include "../ab.h"

typedef struct s_BestMove
{
	float score;
	bool same;
	SDL_Point pos;
	std::vector<SDL_Point> tPoints;
	t_Ability *ability;
	t_AiCharacter *character;
	Character *norm;
}				t_BestMove;

typedef struct s_SomeRetShit
{
	t_AiCharacter *character;
	int type;
}				t_SomeRetShit;

typedef struct s_MoveIter
{
	int abilitySign;
	float score;
	SDL_Point secondaryPos;
	SDL_Point callingPos;
}				t_MoveIter;

typedef struct s_TruthAndScore
{
	bool isIt;
	float score;
}				t_TruthAndScore;

class AiIterator
{
	private:
		std::vector<t_MoveIter> moveSaves = {};
		t_AiMapUnit **map = NULL;
		t_AiCharacter *character = NULL;
		float startScore = 0.0f;
		int depth = 0;
		int moveMoves = 0;
		bool secondLap = false;
		SDL_Point currentIterPosition = {0, 0};
		t_MoveIter currentIterationSave = {};
		t_BestMove action = {0.0f, true, {0, 0}, {}, NULL, NULL};
		void GetPossibleMoves();
		void IterateTheMap();
		void SetAbilityToAction(SDL_Point pos, t_Ability *ability, t_AiMapUnit **newMap, SDL_Point add = {0, 0});
		void SetMoveToAction(SDL_Point pos, t_AiMapUnit **newMap);
		void UseTheAbility(SDL_Point pos, t_Ability *ability, t_AiMapUnit **newMap);
		void HandleAbilityAction(SDL_Point pos, t_Ability *ability);
		void CheckForAbilitySecondTime(SDL_Point pos, int sign);
		void CheckForAbility(SDL_Point pos);
		void CheckForMove(SDL_Point pos);
		int CheckMovePosition(SDL_Point pos);
		void HandleMoveAfterMath(SDL_Point target, int damage, int fatigue);
		void SetDefaultNoCharacter(SDL_Point pos, t_AiMapUnit **map);
		void SetDefaultCharacter(SDL_Point pos, t_AiCharacter *character, t_AiMapUnit **map);
		float SendToNextOne(t_AiMapUnit **map, t_AiCharacter *character, int movered, float score);
		bool RemoveDeadCharacter(t_AiMapUnit **newMap, t_AiCharacter *curr);
		void ParseMoveSaves();
		t_TruthAndScore InSaves(int type, SDL_Point add);
		void AdditionalActions(SDL_Point pos, t_Ability *ability, t_AiMapUnit **map);
		t_AiCharacter *GetCharInMap();
		void IterateMoveSaves();
	public:
		void CalculateMoves(t_AiMapUnit **map, t_AiCharacter *character, float startScore, int depth, int moveMoves);
		t_BestMove GetBestMove() {return(action);};
		float GetBestScore() {return(action.score);};
		~AiIterator() {Destroy();};
		void Destroy();
};

#endif
