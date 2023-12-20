
#ifndef AI_DATA_H
# define AI_DATA_H

# include "../ab.h"

typedef struct s_AiCharacter
{
	Character *character;
	int health;
	int armor;
	int fatigue;
	bool alive;
	int moves;
	SDL_Point position;
}				t_AiCharacter;

#endif
