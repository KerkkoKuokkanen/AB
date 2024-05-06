
#ifndef ABILITIES_H
# define ABILITIES_H

# include "../ab.h"

typedef struct s_Animation
{
	void *animation;
	int type;
}				t_Animation;

typedef struct s_Object
{
	void *object;
	int type;
}				t_Object;

enum {
	DAGGER_OBJ,
	SMOKE_OBJ
};

# define HALF_BLOCK_CHANCE_REDUCE_AMOUNT 1.6f

// Class that is responsible for transfering the data and initiating all the different
// phases of abilities. Not ment to hold any info about abilitites them selves, just responsible for
// launching them into the game and transfering data between the phases of the abilities

class Abilities
{
	private:
		GroundColoring groundColoring;

		std::vector<t_Animation> animations;
		std::vector<t_Object> objects;

		Character *character = NULL;
		Character *target = NULL;
		SDL_Point targetPoint = {0, 0};
		std::vector<SDL_Point> targPoints;

		std::vector<CharacterMover*> misses;

		Selector *selector = NULL;
		TileSelector *tileSelector = NULL;
		MultiSelector *multiSelector = NULL;
		AllSelector *allSelector = NULL;
		PhantomSelector *phantSelector = NULL;
		AxeJumpSelector *axeJumpSelector = NULL;
		SelectorQueue *selectorQueue = NULL;

		Damager damager;
		OpportunityAttack oAttack;
		AbilityOpportunity aoAttack;

		void SetSelector(t_Ability *ability, Character *character);
		void ActivateAbility(t_Ability *ability, Character *character);
		void AnimationUpdater();
		void UpdateThiefAnimation(t_Animation &animation, int index);
		void UpdateLionAnimation(t_Animation &animation, int index);
		void ObjectUpdater();
		void UpdateThiefObject(t_Object &object, int index);
		void UpdatePyroAnimation(t_Animation &animation, int index);
		void UpdateKnightAnimation(t_Animation &animation, int index);
		void UpdateKnightObjects(t_Object &object, int index);
		void UpdateWitchAnimation(t_Animation &animation, int index);
		void UpdateWitchObjects(t_Object &object, int index);
		void CreateShieldBashDamage();
		void UpdateAlchemistAnimation(t_Animation &anim, int index);
		void PyroIncinerateDamage();
		void CreateBombDamages();
		void CreateSlows();
		void AbilityStatus();
		void CreateDamage(bool sound = true);
		void UpdateSelector();
		void SelectorWithCharacters();
		void SelectorWithSquares();
		void SelectorForAxeJump();
		void SelectorQueueUpdate();
		int CreateWitchDamage();
		void UpdatePhantomSelector();
		void MultiSelectorWithCharacter();
		void AllSelectorUpdate();
		void UpdateRotate(int index);
		void HandleDamageVector(std::vector<t_HitReturn> &ret);
		void UpdateMisses();
		void UpdateSmithAnimation(t_Animation &anim, int index);
		void UpdateEnemyAnimationOne(t_Animation &anim, int index);
		void UpdateMageAnimation(t_Animation &anim, int index);
		void UpdateRaiderAnimation(t_Animation &anim, int index);
		void UpdateMageObject(t_Object &object, int index);
		bool CheckGenericAnimations(t_Animation &anim, int index);
		void IncudeToolPoints(TileSelector *used);
		SDL_Point FindToolBox(TileSelector *selec);
	public:
		~Abilities() {Destroy();};
		t_Ability *ability = NULL;
		EffectUpdater effectUpdater;
		bool inMotion = false;
		bool active = false;
		bool marking = false;
		void SetAbility(t_Ability *ability, Character *character);
		void SetMap() {groundColoring.SetMap();};
		void AddMiss(CharacterMover *miss) {misses.push_back(miss);};
		void SetAiAbilityToAction(t_Ability *ability, Character *character, SDL_Point target, std::vector<SDL_Point> &adds);
		Character *GetCharacter() {return (character);};
		t_Animation *GetAnimation(int type);
		void Upadte();
		void Clear();
		void ClearMap();
		void CreateOpportunityDamage(SDL_Point damager, Character *target);
		void CreatePoisonDamage(Character *target, int amount);
		void CreateBleedDamage(Character *target, int amount);
		void RemoveCharacterFromDamager(Character *character) {damager.RemoveDamageFromCreator(character);};
		int GetMarkedAmountForPosition(SDL_Point pos);
		void Destroy();
};

#endif
