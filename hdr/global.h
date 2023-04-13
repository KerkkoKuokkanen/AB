
#ifndef GLOBAL_H
# define GLOBAL_H

# include "ab.h"
# include "classes/renderer.h"
# include "classes/battleGround.h"

# define ALPHA_BLEND 80

typedef struct s_Battle
{
	BattleGround *ground;
	int xDist;
	int yDist;
}				t_Battle;


typedef struct	s_GameState
{
	t_Screen screen;
	t_Camera camera;
	t_Keys keys;
	Renderer *render;
	t_Battle battle;
}				t_GameState;

extern t_GameState gameState;

#endif
