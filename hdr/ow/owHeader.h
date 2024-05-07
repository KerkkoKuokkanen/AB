
#ifndef OW_HEADER_H
# define OW_HEADER_H
#define FRAME 17

# include "../render/renderer.h"
# include "../tools/keys.h"
# include "../render/camera.h"
# include <vector>

typedef struct s_owTileTexts
{
	SDL_Texture *tileOutline;
	SDL_Texture *grassTile;
}				t_owTileTexts;

typedef struct s_owTextures
{
	t_owTileTexts tileTexts;
}				t_owTextures;

typedef struct s_owState
{
	Renderer *renderer;
	t_owTextures textures;
	t_Keys owKeys;
}				t_owState;

extern t_owState owState;

void	eventPoller(t_Keys &keys, int &x, int &y);
void	OverWorldLoop();

#endif
