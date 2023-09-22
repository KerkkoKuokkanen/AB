
#ifndef GLOBAL_H
# define GLOBAL_H

# include "ab.h"
# include "render/renderer.h"
# include "battleClasses/battleGround.h"

# define ALPHA_BLEND 80
# define PI 3.14159

namespace FontTypes
{
	enum {
		GOOGLE_TEXT,
		FIRE,
		NEUE,
		GOOGLE_BOLD
	};
};

namespace Channels
{
	enum {
		DEFAULT_CHANNEL,
		FIRST_CHANNEL,
		THIEF_STEP_CHANNEL,
		DAGGER_THROW0,
		DAGGER_THROW1,
		WHIFF,
		DAGGER_THROW_ANIM,
		SMOKE_THROW,
		SMOKE_BOMB,
		DAGGER_SLASH,
		FLAME_PORT1,
		FLAME_PORT2,
		FLAME_PORT3,
		TURN_START,
		FLAME_SLASH,
		SELECT,
		FLAME_BLAST_EXPLOSION,
		FLAME_BLAST_CHARGE,
		FLAME_BLAST_LAUNCH,
		DEBUFF,
		INCINERATE_CHARGE,
		INCINERATE_SPIN,
		INCINERATE_EXP,
		INCINERATE_MOLO,
		INCINERATE_EXP_SOUND,
		LION_SMACK,
		STUN,
		PHANTOM_KNIGHT,
		ROTATE,
		POOF,
		LOWER_VOLUME_HIT,
		LOWER_VOLUME_WHIFF,
		OPPORTUNIRY,
		KILL_FADE,
		KILL_EXPLOSION0,
		HAMMER_SMACK,
		SUPPLY,
		TOOL_THROW,
		BOX_LANDING,
		BOX_LANDING2,
		PICK_TOOLS,
		BUFF_EFFECT
	};
}

typedef struct s_Battle
{
	BattleGround *ground;
	int xDist;
	int yDist;
	int defaultYAdd;
	int yHeightAdd;
}				t_Battle;

typedef struct s_StatusSurfaces
{
	SDL_Surface *questionMark;
	SDL_Surface *burn;
	SDL_Surface *buff;
}				t_StatusSurfaces;

typedef struct s_Surfaces
{
	t_StatusSurfaces statuses;
	SDL_Surface *thiefIdle1;
	SDL_Surface *thiefIdle2;
	SDL_Surface *skeleIdle1;
	SDL_Surface *skeleIdle2;
	SDL_Surface *pyroIdle1;
	SDL_Surface *pyroIdle2;
	SDL_Surface *energy[2];
	SDL_Surface *turnOrder[2];
	SDL_Surface *bar[2];
	SDL_Surface *treesLeft[4];
	SDL_Surface *treesRight[4];
	SDL_Surface *slashTrail;
	SDL_Surface *counter;
	SDL_Surface *lionIdle1;
	SDL_Surface *lionIdle2;
	SDL_Surface *smithIdle1;
	SDL_Surface *smithIdle2;
	SDL_Surface *mageIdle1;
	SDL_Surface *mageIdle2;
}				t_Surfaces;

typedef struct s_Stands
{
	SDL_Texture *thiefIdle1Stand;
	SDL_Texture *thiefIdle2Stand;
	SDL_Texture *skeleIdle1Stand;
	SDL_Texture *skeleIdle2Stand;
	SDL_Texture *pyroStand;
	SDL_Texture *lionStand;
	SDL_Texture *smithStand;
	SDL_Texture *mageStand;
}				t_Stands;

typedef struct s_CharacterTexts
{
	SDL_Texture *pyroIdle1;
	SDL_Texture *pyroIdle2;
	SDL_Texture *flameSlash[2];
	SDL_Texture *pyroFlameBlast;
	SDL_Texture *pyroAttack[2];
	SDL_Texture *pyroAttackParts;
	SDL_Texture *lionIdle[2];
	SDL_Texture *lionSmack;
	SDL_Texture *smithIdle[2];
	SDL_Texture *handTools[4];
	SDL_Texture *toolBox;
	SDL_Texture *mageIdle[2];
	SDL_Texture *mageIndicator;
}				t_CharacterTexts;

typedef struct s_AttackTextures
{
	SDL_Texture *fireBall[2];
	SDL_Texture *fireBallExplosion;
	SDL_Texture *fireBallAura;
	SDL_Texture *incinerate[2];
	SDL_Texture *incExplosion;
	SDL_Texture *lionTrail;
	SDL_Texture *hammerSmack[2];
	SDL_Texture *toolThrow[2];
	SDL_Texture *smithBuff;
	SDL_Texture *buffLight[2];
	SDL_Texture *mageAttack;
}				t_AttackTextures;

typedef struct s_StatusSprites
{
	SDL_Texture *burns[3];
}				t_StatusSprites;

typedef struct s_Ascii
{
	SDL_Texture *whiteNumbers[10];
	SDL_Texture *normalNumbers[10];
	SDL_Texture *slash;
}				t_Ascii;

typedef struct s_ButtonTextures
{
	SDL_Texture *incinerate;
}				t_ButtonTextures;

typedef struct s_Textures
{
	t_Stands stands;
	t_AttackTextures attacks;
	t_CharacterTexts chars;
	t_Ascii ascii;
	t_StatusSprites statuses;
	t_ButtonTextures buttonTextures;
	SDL_Texture *thiefIdle1;
	SDL_Texture *thiefIdle2;
	SDL_Texture *thiefDaggerThrow;
	SDL_Texture *thiefSmokeThrow[2];
	SDL_Texture *thiefSlash[2];
	SDL_Texture *skeleIdle1;
	SDL_Texture *skeleIdle2;
	SDL_Texture *dust;
	SDL_Texture *turnOrder[2];
	SDL_Texture *turnIndicator;
	SDL_Texture *KillParticle[2];
	SDL_Texture *bar[2];
	SDL_Texture *barFiller;
	SDL_Texture *smallerBar;
	SDL_Texture *thiefAbilites[3];
	SDL_Texture *pyroAbilities[4];
	SDL_Texture *lionAbilities[3];
	SDL_Texture *turnDone;
	SDL_Texture *energy[2];
	SDL_Texture *weaponObjs[1];
	SDL_Texture *treesLeft[4];
	SDL_Texture *treesRight[4];
	SDL_Texture *blocks[2];
	SDL_Texture *smokes[4];
	SDL_Texture *smokeBomb;
	SDL_Texture *MISS;
	SDL_Texture *marker;
	SDL_Texture *counter;
	SDL_Texture *questionMark;
	SDL_Texture *control;
	SDL_Texture *everyColor;
	SDL_Texture *smithAbilities[5];
	SDL_Texture *supplySymbol;
	SDL_Texture *reSupply;
	SDL_Texture *throwObj;
	SDL_Texture *supplyToolSymbol;
	SDL_Texture *buffSymbol;
	SDL_Texture *mageAbilities[3];
}				t_Textures;

typedef struct s_Audio
{
	Mix_Chunk *TFootStep[3];
	Mix_Chunk *daggerThrow[2];
	Mix_Chunk *flamePort[3];
	Mix_Chunk *throwAnim;
	Mix_Chunk *smokeBomb;
	Mix_Chunk *smokeThrow;
	Mix_Chunk *daggerSlash;
	Mix_Chunk *whiff;
	Mix_Chunk *turnStart;
	Mix_Chunk *flameSlash;
	Mix_Chunk *select;
	Mix_Chunk *flameBlast[3];
	Mix_Chunk *debuff;
	Mix_Chunk *incinerate[5];
	Mix_Chunk *lionSmack;
	Mix_Chunk *stun;
	Mix_Chunk *phantomKnight;
	Mix_Chunk *rotate;
	Mix_Chunk *poof;
	Mix_Chunk *opportunity;
	Mix_Chunk *kills[2];
	Mix_Chunk *hammerSmack;
	Mix_Chunk *supply;
	Mix_Chunk *toolThrow;
	Mix_Chunk *boxLand;
	Mix_Chunk *boxLand2;
	Mix_Chunk *pickTools;
	Mix_Chunk *deBuffEffect;
	Mix_Chunk *BuffEffect;
}				t_Audio;

typedef struct s_Fonts
{
	TTF_Font *googleFont;
	TTF_Font *googleBold;
	TTF_Font *fire;
	TTF_Font *neue;
}				t_Fonts;

typedef struct s_MouseOver
{
	bool overAnything;
	bool overAnythingButCharacter;
	bool overTurnOrder;
	bool overMenu;
	bool overCharacterUI;
	bool overCharacter;
}				t_MouseOver;

typedef struct s_Updates
{
	std::vector<Dust*> dusts;
	TurnOrder *turnOrder;
	TurnIndicator *indicator;
	Kill *killer;
	ParticleManager *partManager;
	CharacterUI *UI;
	OBJ_Update *objUpdate;
	Abilities *abilities;
	Info *info;
	float fadeIter;
	int characterAnimIter;
	int characterAnimIndex;
	t_MouseOver hover;
	Character *chosen;
}				t_Updates;

typedef struct	s_ScreenShake
{
	int xShake;
	int yShake;
	int shakeCounter;
	int shakeVolume;
}				t_ScreenShake;

typedef struct	s_GameState
{
	t_wr wr;
	t_Screen screen;
	t_Camera camera;
	t_Modes modes;
	t_Keys keys;
	Renderer *render;
	t_Battle battle;
	t_Fonts fonts;
	t_Textures textures;
	t_Surfaces surfaces;
	t_Updates updateObjs;
	t_Audio audio;
	t_ScreenShake screenShake;
}				t_GameState;

extern t_GameState gameState;

#endif
