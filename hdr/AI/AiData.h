
#ifndef AI_DATA_H
# define AI_DATA_H

# include "../ab.h"

# define AI_TARGET_TYPE_ALLIES 0
# define AI_TARGET_TYPE_ENEMIES 1
# define AI_TARGET_TYPE_BOTH 2

typedef struct s_ControlUnit
{
	bool controlled;
	bool meleeOnlyAlly;
	bool meleeOnlyEnemy;
	std::vector<Character*> controllers;
	int types;
}				t_ControlUnit;

typedef struct s_AiAbility
{
	t_Ability *ability;
	int targetType;
}				t_AiAbility;

typedef struct s_AiCharacter
{
	Character *character;
	std::vector<t_AiAbility> abilities;
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
}				t_AiData;

#endif
