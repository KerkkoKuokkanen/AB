
#ifndef AB_H
# define AB_H

# define FRAME 17

# define FLIP_NONE 0
# define FLIP_HORIZONTAL 1
# define FLIP_VERTICAL 2

# include "../SDL2/SDL.h"
# include "classes/vector.h"

SDL_FRect	translateSprite(SDL_Rect dest, bool staticSprite);

# include "classes/sprite.h"
# include <vector>

typedef struct	s_wr
{
	SDL_Window *win;
	SDL_Renderer *rend;
}				t_wr;

typedef struct s_Screen
{
	int width, height;
	float unit;
	float aspectRatio;
	int midPointX, midPointY;
	float xPixelUnit, yPixelUnit;
}				t_Screen;

typedef struct s_Camera
{
	int x, y;
	float zoom;
	int clickTimePosX, clickTimePosY;
}				t_Camera;

typedef struct s_Keys
{
	int w, a, s, d;
	int click;
	int middleMouse;
	int wheel;
}				t_Keys;

int			figure_the_delay(clock_t start, clock_t end);
void		init(t_wr *wr);
SDL_Texture	*get_texture(SDL_Renderer *rend, const char *filePath);
void		eventPoller();
void		init(t_wr *wr);
int			rounding(float value);
void		CreateGroundTest();

#endif