
#ifndef GLOBAL_H
# define GLOBAL_H

# include "ab.h"
# include "classes/renderer.h"

typedef struct	s_GameState
{
	t_Screen screen;
	t_Camera camera;
	t_Keys keys;
	Renderer *render;
}				t_GameState;

extern t_GameState gameState;

#endif
