
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
# define LAYER_ORDER_SORT 4

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
	LINE_LAYER,
	DUST_LAYER,
	PARTICLE_LAYER,
	OBJECT_LAYER,
	FILTER_LAYER,
	INFO_LAYER,
	TURN_ORDER_LAYER,
	TEXT_LAYER,
	COUNTER_LAYER
};

enum {
	TURN_DONE,
	DAGGER_THROW,
	SMOKE_BOMB,
	DAGGER_SLASH,
	FLAME_PORT,
	FLAME_SLASH,
	FLAME_BLAST,
	INCINERATE,
	LION_SMACK,
	PHANTOM_KNIGHT,
	ROTATE,
	HAMMER_SMACK,
	GO_FOR_THE_HEAD,
	THROW_TOOLBOX,
	SUPPLY_ALLY,
	SUPPLY,
	GENERIC_TOOL_THROW,
	PICK_UP_TOOLS,
	SMITH_BUFF,
	LIGHTNING_BOLT,
	ROCK_FALL,
	HOST_EYES,
	AXE_SLASH,
	AXE_JUMP,
	TOXIC_BLADE,
	RAIDER_BLOCK,
	NAIL_BOMB,
	ACID_BOMB,
	SLOW_BOMB,
	FLAIL_STRIKE,
	SHILED_BASH,
	CONTROL_ZONE
};

namespace StatusSigns
{
	enum {
		STUN,
		BURN,
		BUFF,
		DEBUFF,
		HOST,
		HOSTING,
		TOXIC_BLADE,
		POISON,
		BLEED,
		SLOWED
	};
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
	int fatigue;
	int range;
	int baseChance;
	int statType;
	int statusSign;
	void *stats;
}				t_Ability;

typedef struct s_HitReturn
{
	SDL_Point target;
	bool missing;
}				t_HitReturn;

SDL_FRect	translateSprite(SDL_Rect dest);
SDL_FRect	staitcTranslateSprite(SDL_Rect dest);
SDL_FRect	translateSpriteWithoutScale(SDL_Rect dest);

# include "render/sprite.h"
# include <vector>
# include "statStructs.h"
# include "battleClasses/character.h"
# include "particle/dust.h"
# include "statStructs.h"
# include "battleClasses/turnOrder.h"
# include "battleClasses/turnIndicator.h"
# include "battleClasses/killEffect.h"
# include "battleClasses/kill.h"
# include "particle/particle.h"
# include "particle/particleManager.h"
# include "info/snippet.h"
# include "info/flyingText.h"
# include "tools/throwArch.h"
# include "tools/spriteMover.h"
# include "UI/number.h"
# include "UI/marker.h"
# include "UI/statuses.h"
# include "UI/bar.h"
# include "UI/fatigueBar.h"
# include "UI/button.h"
# include "UI/energy.h"
# include "objects/toolBox.h"
# include "objects/object.h"
# include "objects/objUpdate.h"
# include "effects/buffEffect.h"
# include "effects/hostEffect.h"
# include "effects/slowedEffect.h"
# include "effects/nailBombBlast.h"
# include "effects/hostEyesEffect.h"
# include "effects/acidBombBlast.h"
# include "info/healthColoring.h"
# include "info/supplyEffect.h"
# include "info/control.h"
# include "info/colorEffect.h"
# include "info/controlSetter.h"
# include "info/counter.h"
# include "info/stunUpdates.h"
# include "info/movementEnergy.h"
# include "info/infoBar.h"
# include "info/info.h"
# include "battleClasses/groundColoring.h"
# include "ability/damages/addStatus.h"
# include "ability/characterMover.h"
# include "ability/objects/fireBall.h"
# include "ability/objects/phantomKnight.h"
# include "ability/objects/lightningBolt.h"
# include "ability/objects/rockFall.h"
# include "ability/animation/rotate.h"
# include "ability/animation/goForTheHead.h"
# include "ability/animation/supply.h"
# include "ability/animation/shieldBash.h"
# include "ability/animation/knightAttack.h"
# include "ability/animation/hostEyesAnim.h"
# include "ability/animation/pickUpToolBox.h"
# include "ability/animation/supplyAlly.h"
# include "ability/animation/axeSlash.h"
# include "ability/animation/nailBomb.h"
# include "ability/animation/acidBombAnim.h"
# include "ability/animation/axeJumpAnim.h"
# include "ability/animation/thoolThrowAnim.h"
# include "ability/animation/toxinBuff.h"
# include "ability/animation/smithBuff.h"
# include "ability/animation/hammerSmack.h"
# include "ability/animation/slowBomb.h"
# include "ability/animation/incinerateAnim.h"
# include "ability/animation/flameBlast.h"
# include "ability/animation/phantomAnim.h"
# include "ability/animation/flamePortAnim.h"
# include "ability/animation/daggerSlashAnim.h"
# include "ability/animation/mageAttack.h"
# include "ability/animation/smokeBombAnim.h"
# include "ability/animation/lionSmackAnim.h"
# include "ability/animation/daggerThrowAnim.h"
# include "ability/animation/raiderBlock.h"
# include "ability/animation/flameSlash.h"
# include "ability/objects/smokeEffect.h"
# include "ability/objects/smokeBomb.h"
# include "ability/objects/dagger.h"
# include "ability/objects/bashMover.h"
# include "ability/damages/damageCreator.h"
# include "ability/effectUpdater.h"
# include "ability/damages/Damager.h"
# include "ability/damages/abilityOpportunity.h"
# include "ability/damages/opportunity.h"
# include "ability/selectors/allSelector.h"
# include "ability/selectors/selector.h"
# include "ability/selectors/selectorForTiles.h"
# include "ability/selectors/multiSelector.h"
# include "ability/selectors/phantomSelector.h"
# include "ability/selectors/axeJumpSelector.h"
# include "ability/animation/genericToolThrow.h"
# include "ability/abilities.h"
# include "UI/battleUI.h"

enum {
	THIEF,
	SKELE,
	PYRO,
	LION,
	SMITH,
	MAGE,
	RAIDER,
	ALCHEMIST,
	KNIGHT
};

enum {
	REGULAR_BLOCK,
	FILLER_BLOCK,
	TOP_CORNER_BLOCK,
	TOP_LEFT_BLOCK,
	TOP_RIGHT_BLOCK,
	TOP_REGULAR_BLOCK
};

namespace AdditionalObjects
{
	enum {
		TOOLBOX,
		PHANTOM_KNIGHT
	};
};


typedef struct s_Additional
{
	int type;
	void *object;
}				t_Additional;

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
	t_Additional additional;
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

typedef struct s_Modes
{
	int filterMode;
	bool disableBars;
}				t_Modes;

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
	int control;
}				t_Keys;

int				figure_the_delay(clock_t start, clock_t end);
void			init(t_wr *wr);
SDL_Texture		*get_text(const char *text ,int fontType);
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
Vector			GetCharacterTopMid(Character *character);

t_GMU *getMapTopRight(SDL_Point pos);
t_GMU *getMapTopLeft(SDL_Point pos);
t_GMU *getMapDownRight(SDL_Point pos);
t_GMU *getMapDownLeft(SDL_Point pos);

void SetDelayer(int delayAddition);

int			getXToRight(SDL_Point pos);
int			getXToLeft(SDL_Point pos);
int			GetFromPointY(SDL_Point position, SDL_Point nextPoint);
int			GetFromPointX(SDL_Point position, SDL_Point nextPoint);
SDL_Point	GetPositionFromCoordinates(SDL_Point position, SDL_Point nextPoint);
SDL_Point	GetValidPositionFromCoordinates(SDL_Point position, SDL_Point nextPoint);

void PrintStat();

void		CreatePoisonSnippet(Character *target, int totalAmount, Color color);
void		CreateDamageSnippet(SDL_Point damager, Character *target, int totalDamage, bool opportunity = false);
void		CreateTextSnippet(Character *damager, Character *target, const char *text, int size, Color color);
void		CreateMiss(SDL_Point damager, SDL_Point target, Character *targ, bool sound = false);

void		ExtendPhantSelector(Character *mage, PhantomSelector *selector);
void		ExtendSelector(Character *mage, Selector *selector);

void		UpdateStatuses();
void		ResetStatusUpdates();

bool		StatusApply(t_Ability *ability, Character *character, Character *target, bool skipCheck = false);
bool		MoveChanceCheck(t_Ability *ability, Character *character, Character *target);
int			CheckIfBlock(SDL_Point characterPos, SDL_Point targetPos);
int			GetChance(Character *character, Character *target, t_Ability *ability);
bool		CheckIfOpportunityHits(Character *damager, Character *target);
bool		MeleeCheck(Character *character, Character *target, t_Ability *ability);
bool		RangeCheckWithoutBlockers(Character *character, Character *target, t_Ability *ability);

//audio

void	AudioUpdate();
void	CreateVolumeChannels();
void	AudioSetSound(Mix_Chunk *sound, int channel, int loops);
void	PlaySound(Mix_Chunk *clip, int channel, int loops);
void	AudioCreateVolume(int Chan, int volume);
void	AudioCreateChannels(int amount);
void	AudioClear();

#endif