
#ifndef GLOBAL_H
# define GLOBAL_H

# include "ab.h"
# include "classes/renderer.h"
# include "classes/battleGround.h"

# define ALPHA_BLEND 80
# define PI 3.14159

# define THIEF_STEP_CHANNEL 2

typedef struct s_Battle
{
	BattleGround *ground;
	int xDist;
	int yDist;
	int defaultYAdd;
	int yHeightAdd;
}				t_Battle;

typedef struct s_Textures
{
	SDL_Texture *thiefIdle1;
	SDL_Texture *thiefIdle2;
	SDL_Texture *skeleIdle1;
	SDL_Texture *skeleIdle2;
	SDL_Texture *dust;
	SDL_Texture *turnOrder[2];
	SDL_Texture *turnIndicator;
}				t_Textures;

typedef struct s_Audio
{
	Mix_Chunk *TFootStep[3];
}				t_Audio;

typedef struct s_Updates
{
	std::vector<Dust*> dusts;
	TurnOrder *turnOrder;
	TurnIndicator *indicator;
	float fadeIter;
}				t_Updates;

typedef struct	s_GameState
{
	t_Screen screen;
	t_Camera camera;
	t_Keys keys;
	Renderer *render;
	t_Battle battle;
	t_Textures textures;
	t_Updates updateObjs;
	t_Audio audio;
}				t_GameState;

extern t_GameState gameState;

#endif
