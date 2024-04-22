
#ifndef AI_ITERATOR2_H
# define AI_ITERATOR2_H

# include "../ab.h"

typedef struct s_AiMapItem
{
	int type;
	int turns;
	SDL_Point position;
	t_AiCharacter *parent;
	void *item;
}				t_AiMapItem;

class AiIterator2
{
	private:
		int depth = 0;
		uint16_t **movables = NULL;
		t_AiCharacter *current = NULL;
		t_AiCharacter **charQ = NULL;
		t_AiMapItem **mapItems = NULL;
		void MoveToPosition(uint8_t x, uint8_t y);
		void IterateMap();
	public:
		void CalculateMoves(t_AiCharacter *current, t_AiCharacter **charQ, t_AiMapItem **mapItems);
};

#endif
