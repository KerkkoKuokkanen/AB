
#ifndef AB_H
# define AB_H

# define FRAME 17
# define ASPECT_MULTI 1.777f

# define FLIP_NONE 0
# define FLIP_HORIZONTAL 1
# define FLIP_VERTICAL 2

# define LAYER_NO_SORT 0
# define LAYER_YSORT 1
# define LAYER_REVERSE_YSORT 2
# define LAYER_DEPTH_SORT 3

# define TOOL_MAP_SIGN 9933
# define TURN_SIGN -999898

//mouse states
# define NO_CLICK 0
# define INITIAL_CLICK 1
# define HOLD_CLICK 2
# define RELEASE_CLICK 3

//layer defines
enum {
	BATTLEGROUND_LAYER,
	DUST_LAYER,
	PARTICLE_LAYER,
	OBJECT_LAYER,
	MISS_LAYER,
	TURN_ORDER_LAYER
};

enum {
	TURN_DONE,
	DAGGER_THROW,
	SMOKE_BOMB,
	DAGGER_SLASH,
	FLAME_PORT,
	FLAME_SLASH,
	FLAME_BLAST
};

# include "../SDL2/SDL.h"
# include "tools/vector.h"
# include "tools/color.h"
# include <iostream>

typedef struct s_TextAndSur
{
	SDL_Texture *text;
	SDL_Surface *sur;
}				t_TextAndSur;

typedef struct s_Ability
{
	int type;
	int cost;
	int baseChance;
	void *stats;
}				t_Ability;

typedef struct s_HitReturn
{
	SDL_Point target;
	bool missing;
}				t_HitReturn;

SDL_FRect	translateSprite(SDL_Rect dest);
SDL_FRect	staitcTranslateSprite(SDL_Rect dest);

# include "render/sprite.h"
# include <vector>
# include "battleClasses/character.h"
# include "particle/dust.h"
# include "battleClasses/turnOrder.h"
# include "battleClasses/turnIndicator.h"
# include "battleClasses/kill.h"
# include "particle/particle.h"
# include "particle/particleManager.h"
# include "UI/number.h"
# include "UI/marker.h"
# include "UI/bar.h"
# include "UI/button.h"
# include "UI/energy.h"
# include "objects/object.h"
# include "objects/objUpdate.h"
# include "battleClasses/groundColoring.h"
# include "ability/characterMover.h"
# include "ability/objects/fireBall.h"
# include "ability/animation/flameBlast.h"
# include "ability/animation/flamePortAnim.h"
# include "ability/animation/daggerSlashAnim.h"
# include "ability/animation/smokeBombAnim.h"
# include "ability/animation/daggerThrowAnim.h"
# include "ability/animation/flameSlash.h"
# include "ability/objects/smokeEffect.h"
# include "ability/objects/smokeBomb.h"
# include "ability/objects/dagger.h"
# include "ability/damageCreator.h"
# include "ability/effectUpdater.h"
# include "ability/Damager.h"
# include "ability/selectors/selector.h"
# include "ability/selectors/selectorForTiles.h"
# include "ability/selectors/multiSelector.h"
# include "ability/miss.h"
# include "ability/abilities.h"
# include "UI/battleUI.h"

enum {
	THIEF,
	SKELE,
	PYRO
};

enum {
	REGULAR_BLOCK,
	FILLER_BLOCK,
	TOP_CORNER_BLOCK,
	TOP_LEFT_BLOCK,
	TOP_RIGHT_BLOCK,
	TOP_REGULAR_BLOCK
};

typedef struct s_GroundMapUnit
{
	int tile;
	int height;
	int highlited;
	Character *character;
	bool active;
	bool marked;
	bool blocked;
	Object *obj;
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
	float xStaticUnit, yStaticUnit;
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
	int left, right, up, down;
	int click;
	int rightClick;
	int middleMouse;
	int wheel;
	int mouseX;
	int mouseY;
	int staticMouseX;
	int staticMouseY;
	int smX;
	int smY;
	int space;
	int shift;
}				t_Keys;

int				figure_the_delay(clock_t start, clock_t end);
void			init(t_wr *wr);
SDL_Texture		*get_texture(SDL_Renderer *rend, const char *filePath);
t_TextAndSur	get_texture_and_surface(SDL_Renderer *rend, const char *filePath);
SDL_Texture		*get_texture_with_scale_mode(SDL_Renderer *rend, const char *filePath, SDL_ScaleMode scaleMode);
t_TextAndSur	get_texture_and_surface_with_scale_mode(SDL_Renderer *rend, const char *filePath, SDL_ScaleMode scaleMode);
void			eventPoller();
void			init(t_wr *wr);
int				rounding(float value);
void			CreateGroundTest();
bool			pointCheck(SDL_Point &point, SDL_Rect &hitBox);
bool			modPointCheck(SDL_Point &point, SDL_Rect &hitBox);
bool			CheckInsideShape(SDL_Point up, SDL_Point left, SDL_Point down, SDL_Point right, SDL_Point target);
bool			boxCheck(SDL_Rect box1, SDL_Rect box2);
float			vectorAngle(Vector v1, Vector v2);
void 			vectorRotate(Vector &vec, float angle);
int				degree(float angle);
float			float_rand();
void			CreateDust(SDL_Point position, Vector direction);
void			PlaySound(Mix_Chunk *clip, int channel, int loops);
void			Utility();
void			ObjUpdate();
void			findMovables(int **map, int moves, SDL_Point start);
void			findMovablesStatic(int **map, int moves, SDL_Point start);
Character		*HoveringOver();
void			ManageTextureHovering();
bool			MenuHoverCheck(SDL_Surface *sur, SDL_Rect dest, int xMouse, int yMouse);
void			CreateParticlesForSmokeEffect(SDL_Point pos);
void			UpdateHoveredCharacter();
SDL_Surface		*getSurface(Character *character);
Vector			getDirection(Vector generalDir);
void			SetScreenShake(int volume, int time);
void			ShakeTheScreen();
MISS			*createBasicMISS(SDL_Point start, SDL_Point target, bool sound);

t_GMU *getMapTopRight(SDL_Point pos);
t_GMU *getMapTopLeft(SDL_Point pos);
t_GMU *getMapDownRight(SDL_Point pos);
t_GMU *getMapDownLeft(SDL_Point pos);

int getXToRight(SDL_Point pos);
int getXToLeft(SDL_Point pos);

int			CheckIfBlock(SDL_Point characterPos, SDL_Point targetPos);
int			GetChance(Character *character, Character *target, t_Ability *ability);
bool		MeleeCheck(Character *character, Character *target, t_Ability *ability);
Character	*RangedCheck(Character *character, Character *target, int &chance);

#endif