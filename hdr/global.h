
#ifndef GLOBAL_H
# define GLOBAL_H

# include "ab.h"
# include "render/renderer.h"
# include "battleClasses/battleGround.h"

# define ALPHA_BLEND 80
# define PI 3.14159

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
		FLAME_BLAST_LAUNCH
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

typedef struct s_Surfaces
{
	SDL_Surface *thiefIdle1;
	SDL_Surface *thiefIdle2;
	SDL_Surface *skeleIdle1;
	SDL_Surface *skeleIdle2;
	SDL_Surface *pyroIdle1;
	SDL_Surface *pyroIdle2;
	SDL_Surface *energy[2];
	SDL_Surface *turnOrder[2];
	SDL_Surface *bar[2];
	SDL_Surface *trees[5];
	SDL_Surface *slashTrail;
}				t_Surfaces;

typedef struct s_Stands
{
	SDL_Texture *thiefIdle1Stand;
	SDL_Texture *thiefIdle2Stand;
	SDL_Texture *skeleIdle1Stand;
	SDL_Texture *skeleIdle2Stand;
	SDL_Texture *pyroStand;
}				t_Stands;

typedef struct s_CharacterTexts
{
	SDL_Texture *pyroIdle1;
	SDL_Texture *pyroIdle2;
	SDL_Texture *flameSlash[2];
	SDL_Texture *pyroFlameBlast;
}				t_CharacterTexts;

typedef struct s_AttackTextures
{
	SDL_Texture *fireBall[2];
	SDL_Texture *fireBallExplosion;
	SDL_Texture *fireBallAura;
}				t_AttackTextures;

typedef struct s_Ascii
{
	SDL_Texture *whiteNumbers[10];
	SDL_Texture *slash;
}				t_Ascii;

typedef struct s_Textures
{
	t_Stands stands;
	t_AttackTextures attacks;
	t_CharacterTexts chars;
	t_Ascii ascii;
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
	SDL_Texture *thiefAbilites[3];
	SDL_Texture *pyroAbilities[3];
	SDL_Texture *turnDone;
	SDL_Texture *energy[2];
	SDL_Texture *weaponObjs[1];
	SDL_Texture *trees[5];
	SDL_Texture *blocks[2];
	SDL_Texture *smokes[4];
	SDL_Texture *smokeBomb;
	SDL_Texture *MISS;
	SDL_Texture *marker;
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
}				t_Audio;

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
	t_Screen screen;
	t_Camera camera;
	t_Keys keys;
	Renderer *render;
	t_Battle battle;
	t_Textures textures;
	t_Surfaces surfaces;
	t_Updates updateObjs;
	t_Audio audio;
	t_ScreenShake screenShake;
}				t_GameState;

extern t_GameState gameState;

#endif
