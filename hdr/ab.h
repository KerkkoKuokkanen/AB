
#ifndef AB_H
# define AB_H

# define FRAME 17
# define ASPECT_MULTI 1.777f

# define TOOL_MAP_SIGN 9933
# define TOOL_MAP_BLOCKER 9934
# define TURN_SIGN -999898

//mouse states
# define NO_CLICK 0
# define INITIAL_CLICK 1
# define HOLD_CLICK 2
# define RELEASE_CLICK 3

//layer defines
enum {
	BACK_GROUND,
	BATTLEGROUND_LAYER,
	LINE_LAYER,
	DUST_LAYER,
	FLAME_PORT_LAYER,
	TELEPORT_LAYER,
	PARTICLE_LAYER,
	OBJECT_LAYER,
	FILTER_LAYER,
	INFO_LAYER,
	TURN_ORDER_LAYER,
	TEXT_LAYER,
	COUNTER_LAYER,
	TEXT_BUBBLE_LAYER,
	MENU_LAYER
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
	CONTROL_ZONE,
	ACID_RAIN,
	TELEPORT,
	HEALTH_TRANSFER,
	SKELE_MELEE,
	SKELE_LUNGE,
	BIG_THUG_STRIKE,
	THUG_STRIKE,
	BIG_THUG_INSPIRE
};

namespace StatusSigns
{
	enum {
		BIG_CHARACTER,
		STUN,
		BURN,
		BUFF,
		DEBUFF,
		HOST,
		HOSTING,
		TOXIC_BLADE,
		POISON,
		BLEED,
		SLOWED,
		CONTROL,
		FRENZY
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
	int damage;
	int critChance;
	bool melee;
	bool targetAdds;
	void *stats;
}				t_Ability;

typedef struct s_HitReturn
{
	SDL_Point target;
	bool missing;
}				t_HitReturn;

typedef struct s_Additional
{
	int type;
	void *object;
}				t_Additional;

SDL_FRect	translateSprite(SDL_Rect dest);
SDL_FRect	staitcTranslateSprite(SDL_Rect dest);
SDL_FRect	translateSpriteWithoutScale(SDL_Rect dest);

# include "tools/keys.h"
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
# include "info/texts/textBubble.h"
# include "UI/texts/UiTextUpdater.h"
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
# include "effects/healEffect.h"
# include "effects/frenzyColorer.h"
# include "effects/thugInspire.h"
# include "effects/slowedEffect.h"
# include "effects/nailBombBlast.h"
# include "effects/hostEyesEffect.h"
# include "effects/acidBombBlast.h"
# include "effects/shieldBashEffect.h"
# include "info/healthColoring.h"
# include "info/supplyEffect.h"
# include "info/control.h"
# include "info/colorEffect.h"
# include "info/controlSetter.h"
# include "info/counter.h"
# include "info/stunUpdates.h"
# include "info/movementEnergy.h"
# include "info/infoBar.h"
# include "info/IconBars/IconHealth.h"
# include "info/IconBars/IconBar.h"
# include "info/IconBars/IconBarHandler.h"
# include "info/menu/menu.h"
# include "info/texts/hitChance.h"
# include "info/texts/statusInfos.h"
# include "info/info.h"
# include "battleClasses/groundColoring.h"
# include "ability/damages/addStatus.h"
# include "ability/characterMover.h"
# include "ability/objects/fireBall.h"
# include "ability/objects/phantomKnight.h"
# include "ability/objects/teleport.h"
# include "ability/objects/lightningBolt.h"
# include "ability/objects/rockFall.h"
# include "ability/objects/healthTransfer.h"
# include "ability/animation/rotate.h"
# include "ability/animation/goForTheHead.h"
# include "ability/animation/supply.h"
# include "ability/animation/shieldBash.h"
# include "ability/animation/knightAttack.h"
# include "ability/animation/hostEyesAnim.h"
# include "ability/animation/pickUpToolBox.h"
# include "ability/animation/supplyAlly.h"
# include "ability/animation/axeSlash.h"
# include "ability/animation/bigThugInspire.h"
# include "ability/animation/thugStrike.h"
# include "ability/animation/bigThugStrike.h"
# include "ability/animation/nailBomb.h"
# include "ability/animation/acidBombAnim.h"
# include "ability/animation/axeJumpAnim.h"
# include "ability/animation/thoolThrowAnim.h"
# include "ability/animation/toxinBuff.h"
# include "ability/animation/smithBuff.h"
# include "ability/animation/hammerSmack.h"
# include "ability/animation/slowBomb.h"
# include "ability/animation/skeleMelee.h"
# include "ability/animation/incinerateAnim.h"
# include "ability/animation/flameBlast.h"
# include "ability/animation/phantomAnim.h"
# include "ability/animation/flamePortAnim.h"
# include "ability/animation/daggerSlashAnim.h"
# include "ability/animation/witchAnimation.h"
# include "ability/animation/mageAttack.h"
# include "ability/animation/controlZone.h"
# include "ability/animation/smokeBombAnim.h"
# include "ability/animation/heartBeat.h"
# include "ability/animation/teleStart.h"
# include "ability/animation/lionSmackAnim.h"
# include "ability/animation/daggerThrowAnim.h"
# include "ability/animation/raiderBlock.h"
# include "ability/animation/skeleLunge.h"
# include "ability/animation/acidRain.h"
# include "ability/animation/flameSlash.h"
# include "ability/objects/smokeEffect.h"
# include "ability/objects/smokeBomb.h"
# include "ability/objects/dagger.h"
# include "ability/objects/bashMover.h"
# include "ability/damages/damageCreator.h"
# include "ability/effectUpdater.h"
# include "ability/damages/Damager.h"
# include "ability/damages/opportunity.h"
# include "ability/damages/abilityOpportunity.h"
# include "ability/selectors/allSelector.h"
# include "ability/selectors/selector.h"
# include "ability/selectors/selectorForTiles.h"
# include "ability/selectors/multiSelector.h"
# include "ability/selectors/phantomSelector.h"
# include "ability/selectors/selectorQueue.h"
# include "ability/selectors/axeJumpSelector.h"
# include "ability/animation/genericToolThrow.h"
# include "ability/abilities.h"
# include "UI/battleUI.h"
# include "AI/AiData.h"
# include "AI/AiIterator.h"
# include "AI/AiObjectHolder.h"

enum {
	THIEF,
	SKELE,
	PYRO,
	LION,
	PHANTOM_LION,
	SMITH,
	MAGE,
	RAIDER,
	ALCHEMIST,
	KNIGHT,
	WITCH,
	TOOLS,
	BIG_THUG,
	THUG
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

typedef struct s_Modes
{
	int filterMode;
	bool disableBars;
}				t_Modes;

int				figure_the_delay(clock_t start, clock_t end);
void			init(t_wr *wr);
void			InitBattle();
SDL_Texture		*get_text(const char *text ,int fontType);
SDL_Texture		*get_texture(SDL_Renderer *rend, const char *filePath);
t_TextAndSur	get_texture_and_surface(SDL_Renderer *rend, const char *filePath);
SDL_Texture		*get_texture_with_scale_mode(SDL_Renderer *rend, const char *filePath, SDL_ScaleMode scaleMode);
t_TextAndSur	get_texture_and_surface_with_scale_mode(SDL_Renderer *rend, const char *filePath, SDL_ScaleMode scaleMode);
void			eventPoller(t_Keys &keys, int &x, int &y);
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
void			findMovablesNormal(t_AiMapUnit **map, int moves, SDL_Point start);
Character		*HoveringOver();
void			ManageTextureHovering();
bool			MenuHoverCheck(SDL_Surface *sur, SDL_Rect dest, int xMouse, int yMouse);
void			CreateParticlesForSmokeEffect(SDL_Point pos);
void			CreateParticlesForThugIntensity0To100(Character *character, int intensity);
void			UpdateHoveredCharacter();
SDL_Surface		*getSurface(Character *character);
SDL_Surface		*getScaleSurface(SDL_Surface *surface, int width, int height);
SDL_Texture		*getScaledTexture(SDL_Surface *sur, int width, int height);
Vector			getDirection(Vector generalDir);
void			SetScreenShake(int volume, int time);
void			ShakeTheScreen();
Vector			GetCharacterTopMid(Character *character);
int				GetDamageReduction(Character *damaged, Character *damager, int damage);

t_GMU *getMapTopRight(SDL_Point pos);
t_GMU *getMapTopLeft(SDL_Point pos);
t_GMU *getMapDownRight(SDL_Point pos);
t_GMU *getMapDownLeft(SDL_Point pos);

int TTBuffProtection(Character *character, TextBubble *bubble, int start);
int TTBuffOppAccuracy(Character *character, TextBubble *bubble, int start);
int TTBuffAccuracy(Character *character, TextBubble *bubble, int start);
int TTDeBuffAccuracy(Character *character, TextBubble *bubble, int start);
int TTDeBuffOppAccuracy(Character *character, TextBubble *bubble, int start);
int TTDeBuffProtection(Character *character, TextBubble *bubble, int start);

void AddBuffToCharacter(Character *target, t_BuffDebuff add);
void AddDeBuffToCharacter(Character *target, t_BuffDebuff add);

void SetDelayer(int delayAddition);

int			getXToRight(SDL_Point pos);
int			getXToLeft(SDL_Point pos);
int			GetFromPointY(SDL_Point position, SDL_Point nextPoint);
int			GetFromPointX(SDL_Point position, SDL_Point nextPoint);
SDL_Point	GetPositionFromCoordinates(SDL_Point position, SDL_Point nextPoint);
SDL_Point	GetValidPositionFromCoordinates(SDL_Point position, SDL_Point nextPoint);

void PrintStat();
bool CheckIfValidPosition(SDL_Point pos);
int CheckIfSmoked(SDL_Point pos);

void InitThugParts();

bool CheckForSize(SDL_Point point1, SDL_Point point2);
bool CheckForMaxHealth(SDL_Point point1, SDL_Point point2);

int DistanceBetweenPoints(SDL_Point one, SDL_Point two);
int DistanceBetweenPointsStatic(SDL_Point one, SDL_Point two);

void		CreatePoisonSnippet(Character *target, int totalAmount, Color color);
void		CreateDamageSnippet(SDL_Point damager, Character *target, int totalDamage, bool opportunity = false);
void		CreateDamageSnippetWithColor(SDL_Point damager, Character *target, int totalDamage, Color col, bool opportunity = false);
void		CreateTextSnippet(Character *damager, Character *target, const char *text, int size, Color color);
void		CreateMiss(SDL_Point damager, SDL_Point target, Character *targ, bool sound = false);

void		ExtendPhantSelector(Character *mage, PhantomSelector *selector);
void		ExtendSelector(Character *mage, Selector *selector);

void		UpdateStatuses();
void		ResetStatusUpdates();

int			GetStatusChance(t_Ability *ability, Character *character, Character *target);
bool		StatusApply(t_Ability *ability, Character *character, Character *target, bool skipCheck = false);
bool		MoveChanceCheck(t_Ability *ability, Character *character, Character *target);
int			CheckIfBlock(SDL_Point characterPos, SDL_Point targetPos);
int			GetChance(Character *character, Character *target, t_Ability *ability);
bool		CheckIfOpportunityHits(Character *damager, Character *target);
bool		MeleeCheck(Character *character, Character *target, t_Ability *ability);

SDL_Point	GetDamageValues(Character *target, Character *caster, t_Ability *ability);
SDL_Point	GetOpportunityDamageValues(Character *target, SDL_Point caster);

//misc

bool CheckForTurnChange();

//AI stuff

bool					AiCheckIfCanHit(t_AiMapUnit **map, t_Ability *ability, t_AiCharacter *character, SDL_Point pos, SDL_Point start);
void					CopyStatusesFromTheCharacter(t_AiCharacter *aiChar, Character *character);
t_SomeRetShit			GetNextCharacter(t_AiCharacter *curr, t_AiCharacter *next, t_AiMapUnit **map);
void					ReturnAiIterator(AiIterator *iterator);
AiIterator				*GetAiIterator();
void					AiCheckForHosting(t_AiCharacter *character, t_AiMapUnit **map);
void					CheckDeadCharacter(t_AiCharacter *character, t_AiMapUnit **map);
bool					SomeOneMoving();
void					InitCrazyLoopForIteration();
void					EndCrazyLoopIteration();
void					CreateDamageToAiCharacter(t_AiCharacter *character, int damage);
int						AiOppDamageNumber(t_AiCharacter *target, t_AiCharacter *caster);
int						AiDamageNumber(t_AiCharacter *target, t_AiCharacter *caster, t_Ability *ability);
bool					AiCheckSmoked(SDL_Point pos, t_AiMapUnit **map);
int						AiGetChance(t_AiCharacter *character, t_AiCharacter *target, t_Ability *ability, t_AiMapUnit **map);
void					AiManaging();
void					AiManagerUpdate();
void					CreateTheMoveMaps();
bool					CheckIfNextToToolBox(SDL_Point pos);
t_AiCharacter			*GetTheStartingTurnForAi(t_AiMapUnit **map);
t_AiMapUnit				**GetTheMap();
float					CrazyLoopScore(t_AiMapUnit **map, std::vector<t_AiCharacter*> &charQ);
float					GetAiScore(t_AiMapUnit **map, t_AiCharacter *current);
void					GetAiMapMoves(t_AiCharacter *aiChar, t_AiMapUnit **map);
t_TargetingType			GetAbilityTargetingType(t_Ability *ability);
t_AiMapUnit				**GetReplica(t_AiMapUnit **map);
void					DestroyMap(t_AiMapUnit **map);
void					InitObjHolder();
t_AiMapUnit				**GetMapFromHolder();
t_AiCharacter			*GetAiCharacterFromHolder();
void					ReturnAiIterator(AiIterator *iterator);
float					GetAiPositionScore(std::vector<t_AiCharacter*> &CQ, t_AiMapUnit **map);
void					OrderTheCharQ(std::vector<t_AiCharacter*> &charQ);
void					ReturnAiCharacter(t_AiCharacter *aiCharacter);
t_AiCharacter			*GetReplicaAiCharacter(t_AiCharacter *copied);
int						AiGetXToRight(SDL_Point pos);
int						AiGetXToLeft(SDL_Point pos);
bool					AiValidPos(SDL_Point pos);
void					InitAiIteration();
uint16_t				**CreateMoveMapForAi2();
void					DestroyMoveMap2(uint16_t **map);
void					ReturnCharQToHolder(t_AiCharacter **charQ);
t_AiCharacter			*GetReplicaAiCharacter(t_AiCharacter *copied);
void					RemoveTheDead(t_AiMapUnit **map, std::vector<t_AiCharacter*> &charQ);
int						RangeBetweenPositionsWithControls(t_AiMapUnit **map ,SDL_Point start, SDL_Point end, bool ally);
int						RangeBetweenPositions(t_AiMapUnit **map ,SDL_Point start, SDL_Point end);
std::vector<SDL_Point>	GetCharacterEffectiveDistances(t_AiCharacter *character);
bool					NoPointInMovingControlChecks(t_AiCharacter *character, t_AiMapUnit **map, std::vector<t_AiCharacter*> &charQ);
t_PointDist				ReturnMapPositionDistances(SDL_Point check, t_AiMapUnit **map, t_AiCharacter *character, int distance, bool staticDist, int targetType, int saveCount, std::vector<t_AiCharacter*> &charQ);

//audio

void	AudioUpdate();
void	CreateVolumeChannels();
void	AudioSetSound(Mix_Chunk *sound, int channel, int loops);
void	PlaySound(Mix_Chunk *clip, int channel, int loops);
void	AudioCreateVolume(int Chan, int volume);
void	AudioCreateChannels(int amount);
void	AudioClear();

void DeltaTimeStart();
void DeltaTimeGet();

#endif