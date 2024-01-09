
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

typedef struct s_AiMapObj
{
	bool obj;
	int size;
}				t_AiMapObj;

typedef struct s_AiAdds
{
	bool phantom;
	bool toolBox;
	std::tuple<bool, int> smoke;
}				t_AiAdds;

typedef struct s_AiMapUnit
{
	bool blocked;
	int height;
	t_AiCharacter character;
	t_AiMapObj obj;
	t_AiAdds adds;
	int movable;
}				t_AiMapUnit;

#endif
