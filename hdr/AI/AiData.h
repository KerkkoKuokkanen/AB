
#ifndef AI_DATA_H
# define AI_DATA_H

# include "../ab.h"

typedef struct s_ControlUnit
{
	bool controlled;
	bool meleeOnlyAlly;
	bool meleeOnlyEnemy;
	std::vector<Character*> controllers;
	int types;
}				t_ControlUnit;

typedef struct s_AiCharacter
{
	Character *character;
	int health;
	int armor;
	bool alive;
}				t_AiCharacter;

typedef struct s_AiMapUnitGeneral
{
	Object *obj;
	t_Additional add;
}				t_AiMapUnitGeneral;

typedef struct s_AiMapUnitSpecial
{
	bool smoked;
	bool toolBoxAbilities;
}				t_AiMapUnitSpecial;

typedef struct s_AiMapUnit
{
	bool blocked;
	int height;
	t_AiMapUnitGeneral generals;
	t_AiMapUnitSpecial specials;
	t_ControlUnit control;
	t_AiCharacter character;
}				t_AiMapUnit;

typedef struct s_AiData
{
	t_AiMapUnit **map;
	std::vector<t_AiCharacter> turnQueue;
	t_AiCharacter current;
}				t_AiData;

#endif
