
#ifndef AB_H
# define AB_H

# define FRAME 17

# define FLIP_NONE 0
# define FLIP_HORIZONTAL 1
# define FLIP_VERTICAL 2

# define LAYER_NO_SORT 0
# define LAYER_YSORT 1
# define LAYER_REVERSE_YSORT 2

# define TOOL_MAP_SIGN 9933
# define TURN_SIGN -999898

//mouse states
# define NO_CLICK 0
# define INITIAL_CLICK 1
# define HOLD_CLICK 2
# define RELEASE_CLICK 3

//layer defines
# define BATTLEGROUND_LAYER 0
# define DUST_LAYER 1
# define PARTICLE_LAYER 2
# define TURN_ORDER_LAYER 3

enum {
	TURN_DONE,
	DAGGER_THROW
};

# include "../SDL2/SDL.h"
# include "classes/vector.h"
# include <iostream>

SDL_FRect	translateSprite(SDL_Rect dest, bool staticSprite);

# include "classes/sprite.h"
# include <vector>
# include "classes/character.h"
# include "classes/dust.h"
# include "classes/turnOrder.h"
# include "classes/turnIndicator.h"
# include "classes/kill.h"
# include "classes/particle.h"
# include "classes/particleManager.h"
# include "classes/bar.h"
# include "classes/button.h"
# include "classes/battleUI.h"

enum {
	THIEF,
	SKELE
};

enum {
	REGULAR_BLOCK,
	FILLER_BLOCK,
	TOP_CORNER_BLOCK,
	TOP_LEFT_BLOCK,
	TOP_RIGHT_BLOCK,
	TOP_REGULAR_BLOCK
};

typedef struct s_TextAndSur
{
	SDL_Texture *text;
	SDL_Surface *sur;
}				t_TextAndSur;

typedef struct s_GroundMapUnit
{
	int tile;
	int height;
	int highlited;
	Character *character;
	bool active;
	bool marked;
	bool blocked;
}				t_GMU;

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
	int rightClick;
	int middleMouse;
	int wheel;
	int mouseX;
	int mouseY;
	int space;
}				t_Keys;

int				figure_the_delay(clock_t start, clock_t end);
void			init(t_wr *wr);
SDL_Texture		*get_texture(SDL_Renderer *rend, const char *filePath);
t_TextAndSur	get_texture_and_surface(SDL_Renderer *rend, const char *filePath);
SDL_Texture		*get_texture_with_scale_mode(SDL_Renderer *rend, const char *filePath, SDL_ScaleMode scaleMode);
void			eventPoller();
void			init(t_wr *wr);
int				rounding(float value);
void			CreateGroundTest();
bool			pointCheck(SDL_Point &point, SDL_Rect &hitBox);
bool			CheckInsideShape(SDL_Point up, SDL_Point left, SDL_Point down, SDL_Point right, SDL_Point target);
bool			boxCheck(SDL_Rect box1, SDL_Rect box2);
float			vectorAngle(Vector v1, Vector v2);
int				degree(float angle);
float			float_rand();
void			CreateDust(SDL_Point position, Vector direction);
void			PlaySound(Mix_Chunk *clip, int channel, int loops);
void			Utility();
void			ObjUpdate();

#endif