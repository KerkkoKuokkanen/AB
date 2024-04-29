
#ifndef AI_ITERATOR2_H
# define AI_ITERATOR2_H
# define SCORE_SAVE_SIZE 33
# define SCORE_NOT_USED -28882

# include "../ab.h"

typedef struct s_AiMapItem
{
	int type;
	int turns;
	SDL_Point position;
	t_AiCharacter *parent;
	t_AiCharacter *own;
	void *item;
}				t_AiMapItem;

typedef struct s_MoverSmover
{
	SDL_Point pos;
	int subLoop;
	float score;
}				t_MoverSmover;

typedef struct s_Ai2MoveSaver
{
	t_MoverSmover moves[SCORE_SAVE_SIZE];
	float smalles;
	int smallesIndex;
}				t_Ai2MoveSaver;

class AiIterator2
{
	private:
		int depth = 0;
		int size = 0;
		bool ally = false;
		uint16_t **movables = NULL;
		t_AiCharacter *current = NULL;
		t_AiCharacter **charQ = NULL;
		t_AiMapItem **mapItems = NULL;
		t_Ai2MoveSaver *savedMoves;
		void CreateSavedMoves();
		void MoveToPosition(uint8_t x, uint8_t y);
		void IterateMap();
	public:
		void CalculateMoves(t_AiCharacter *current, t_AiCharacter **charQ, t_AiMapItem **mapItems);
};

#endif
