
#ifndef GLOBAL_H
# define GLOBAL_H

# include "ab.h"
# include "render/renderer.h"
# include "battleClasses/battleGround.h"
# include "battleClasses/character.h"

# define ALPHA_BLEND 80
# define PI 3.14159

namespace FontTypes
{
	enum {
		GOOGLE_TEXT,
		FIRE,
		NEUE,
		GOOGLE_BOLD,
		GOOGLE_TEXT_SMALL
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
		BUFF_EFFECT,
		MAGE_CAST,
		LIGHTNING,
		METEOR1,
		METEOR2,
		METEOR3,
		HOST_EYES1,
		HOST_EYES2,
		HOST_EYES3,
		AXE_SWING,
		VOLUME_1,
		VOLUME_2,
		VOLUME_3,
		VOLUME_4,
		VOLUME_5,
		VOLUME_6,
		VOLUME_7,
		VOLUME_8,
		VOLUME_9,
		VOLUME_10,
		VOLUME_11,
		VOLUME_12,
		VOLUME_13,
		VOLUME_14,
		VOLUME_15,
		VOLUME_16,
		VOLUME_17,
		VOLUME_18,
		VOLUME_19,
		VOLUME_20,
		VOLUME_21,
		VOLUME_22,
		VOLUME_23,
		VOLUME_24,
		VOLUME_25,
		VOLUME_26,
		VOLUME_27,
		VOLUME_28,
		VOLUME_29,
		VOLUME_30,
		VOLUME_31,
		VOLUME_32,
		VOLUME_33,
		VOLUME_34,
		VOLUME_35,
		VOLUME_36,
		VOLUME_37,
		VOLUME_38,
		VOLUME_39,
		VOLUME_40,
		VOLUME_41,
		VOLUME_42,
		VOLUME_43,
		VOLUME_44,
		VOLUME_45,
		VOLUME_46,
		VOLUME_47,
		VOLUME_48,
		VOLUME_49,
		VOLUME_50,
		VOLUME_51,
		VOLUME_52,
		VOLUME_53,
		VOLUME_54,
		VOLUME_55,
		VOLUME_56,
		VOLUME_57,
		VOLUME_58,
		VOLUME_59,
		VOLUME_60,
		VOLUME_61,
		VOLUME_62,
		VOLUME_63,
		VOLUME_64,
		VOLUME_65,
		VOLUME_66,
		VOLUME_67,
		VOLUME_68,
		VOLUME_69,
		VOLUME_70,
		VOLUME_71,
		VOLUME_72,
		VOLUME_73,
		VOLUME_74,
		VOLUME_75,
		VOLUME_76,
		VOLUME_77,
		VOLUME_78,
		VOLUME_79,
		VOLUME_80,
		VOLUME_81,
		VOLUME_82,
		VOLUME_83,
		VOLUME_84,
		VOLUME_85,
		VOLUME_86,
		VOLUME_87,
		VOLUME_88,
		VOLUME_89,
		VOLUME_90,
		VOLUME_91,
		VOLUME_92,
		VOLUME_93,
		VOLUME_94,
		VOLUME_95,
		VOLUME_96,
		VOLUME_97,
		VOLUME_98,
		VOLUME_99,
		VOLUME_100,
		VOLUME_101,
		VOLUME_102,
		VOLUME_103,
		VOLUME_104,
		VOLUME_105,
		VOLUME_106,
		VOLUME_107,
		VOLUME_108,
		VOLUME_109,
		VOLUME_110,
		VOLUME_111,
		VOLUME_112,
		VOLUME_113,
		VOLUME_114,
		VOLUME_115,
		VOLUME_116,
		VOLUME_117,
		VOLUME_118,
		VOLUME_119,
		VOLUME_120,
		VOLUME_121,
		VOLUME_122,
		VOLUME_123,
		VOLUME_124,
		VOLUME_125,
		VOLUME_126,
		VOLUME_127,
		VOLUME_128
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
	SDL_Surface *hostSymbol;
	SDL_Surface *hostingSymbol;
	SDL_Surface *raiderIdle1;
	SDL_Surface *raiderIdle2;
	SDL_Surface *toxinSym;
	SDL_Surface *poisonSym;
	SDL_Surface *alchemistIdle1;
	SDL_Surface *alchemistIdle2;
	SDL_Surface *bleedSymbol;
	SDL_Surface *slowSymbol;
	SDL_Surface *knightIdle1;
	SDL_Surface *knightIdle2;
	SDL_Surface *control;
	SDL_Surface *witchIdle1;
	SDL_Surface *witchIdle2;
	SDL_Surface *toolBox;
	SDL_Surface *skeleLunge;
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
	SDL_Texture *raiderStand;
	SDL_Texture *knightStand;
	SDL_Texture *witchStand;
	SDL_Texture *toolsStand;
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
	SDL_Texture *phantLions[3];
	SDL_Texture *lionSmack;
	SDL_Texture *smithIdle[2];
	SDL_Texture *handTools[4];
	SDL_Texture *toolBox;
	SDL_Texture *mageIdle[2];
	SDL_Texture *mageIndicator;
	SDL_Texture *raiderIdle[2];
	SDL_Texture *AlchemistIdle[2];
	SDL_Texture *knightIdle[2];
	SDL_Texture *witchIdle[2];
	SDL_Texture *witchSource;
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
	SDL_Texture *lightning;
	SDL_Texture *rockFall;
	SDL_Texture *hostEyes;
	SDL_Texture *newExps[3];
	SDL_Texture *axeSlash[2];
	SDL_Texture *axeJump;
	SDL_Texture *jumpSlash[2];
	SDL_Texture *raiderBlock;
	SDL_Texture *alchemistThrow[2];
	SDL_Texture *bombs[3];
	SDL_Texture *nail;
	SDL_Texture *smithHeadSmack[2];
	SDL_Texture *knightAttack[2];
	SDL_Texture *shieldBash[2];
	SDL_Texture *witchAttack;
	SDL_Texture *glows[3];
	SDL_Texture *rainDrop;
	SDL_Texture *heartBeat[2];
	SDL_Texture *sekeleMelee;
	SDL_Texture *skeleLunge;
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

typedef struct s_IconTextures
{
	SDL_Texture *icons[12];
	SDL_Texture *iconX;
	SDL_Texture *iconBars[3];
}				t_IconTextures;

typedef struct s_Textures
{
	t_Stands stands;
	t_AttackTextures attacks;
	t_CharacterTexts chars;
	t_Ascii ascii;
	t_StatusSprites statuses;
	t_ButtonTextures buttonTextures;
	t_IconTextures iconTexts;
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
	SDL_Texture *smithAbilities[6];
	SDL_Texture *supplySymbol;
	SDL_Texture *reSupply;
	SDL_Texture *throwObj;
	SDL_Texture *supplyToolSymbol;
	SDL_Texture *buffSymbol;
	SDL_Texture *mageAbilities[3];
	SDL_Texture *hostSymbol;
	SDL_Texture *hostingSymbol;
	SDL_Texture *raiderAbilities[4];
	SDL_Texture *toxinSymbol;
	SDL_Texture *poisonSymbol;
	SDL_Texture *alchemistAbilities[3];
	SDL_Texture *bleedSymbol;
	SDL_Texture *slowSymbol;
	SDL_Texture *knightAbilities[3];
	SDL_Texture *filter;
	SDL_Texture *backGround;
	SDL_Texture *witchAbilities[3];
	SDL_Texture *critFilter;
}				t_Textures;

typedef struct s_Audio
{
	Mix_Chunk *TFootStep[3];
	Mix_Chunk *hitEffect;
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
	Mix_Chunk *incinerate[2];
	Mix_Chunk *lionSmack;
	Mix_Chunk *stun;
	Mix_Chunk *phantomKnight;
	Mix_Chunk *rotate;
	Mix_Chunk *poof;
	Mix_Chunk *opportunity;
	Mix_Chunk *kills[3];
	Mix_Chunk *hammerSmack;
	Mix_Chunk *supply;
	Mix_Chunk *toolThrow;
	Mix_Chunk *boxLand;
	Mix_Chunk *boxLand2;
	Mix_Chunk *pickTools;
	Mix_Chunk *deBuffEffect;
	Mix_Chunk *BuffEffect;
	Mix_Chunk *mageCast;
	Mix_Chunk *lightning;
	Mix_Chunk *meteors[3];
	Mix_Chunk *hostEyes[3];
	Mix_Chunk *axeSwing;
	Mix_Chunk *jumpScream;
	Mix_Chunk *raiderJump;
	Mix_Chunk *poison;
	Mix_Chunk *toxicBlade;
	Mix_Chunk *raiderBlock;
	Mix_Chunk *nailBomb;
	Mix_Chunk *bleed;
	Mix_Chunk *acidBomb[3];
	Mix_Chunk *slowBomb[2];
	Mix_Chunk *slowDebuff;
	Mix_Chunk *flailStrike;
	Mix_Chunk *shieldBash[2];
	Mix_Chunk *rainAttack[2];
	Mix_Chunk *teleport[2];
	Mix_Chunk *heartBeat;
	Mix_Chunk *healPart;
	Mix_Chunk *criticalHit;
	Mix_Chunk *skeleMelee;
	Mix_Chunk *skeleLunge;
}				t_Audio;

typedef struct s_Fonts
{
	TTF_Font *googleFont;
	TTF_Font *googleFontSmall;
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
	int delayer;
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

typedef struct s_MovementMap
{
	SDL_Point start;
	int **map;
}				t_MovementMap;

typedef struct s_AiMoveMaps
{
	t_MovementMap **abilities;
	t_MovementMap **staticMoves;
}				t_AiMoveMaps;

extern t_AiMoveMaps moveMaps;

#endif
