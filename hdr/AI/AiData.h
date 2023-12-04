
#ifndef AI_DATA_H
# define AI_DATA_H

# include "../ab.h"

typedef struct s_ControlUnit
{
	bool controlled;
	std::vector<Character*> controllers;
	int types;
}				t_ControlUnit;



typedef struct s_AiData
{
	
}				t_AiData;

#endif
