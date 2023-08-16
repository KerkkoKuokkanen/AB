
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
		std::vector<MISS*> misses;

		t_Ability *ability = NULL;
		Character *character = NULL;
		Character *target = NULL;
		SDL_Point targetPoint = {0, 0};
		std::vector<SDL_Point> targPoints;

		Selector *selector = NULL;
		TileSelector *tileSelector = NULL;
		MultiSelector *multiSelector = NULL;
		AllSelector *allSelector = NULL;
		PhantomSelector *phantSelector = NULL;
		Damager damager;
		OpportunityAttack oAttack;

		void SetSelector(t_Ability *ability, Character *character);
		void ActivateAbility(t_Ability *ability, Character *character);
		void AnimationUpdater();
		void UpdateThiefAnimation(t_Animation &animation, int index);
		void UpdateLionAnimation(t_Animation &animation, int index);
		void ObjectUpdater();
		void UpdateThiefObject(t_Object &object, int index);
		void UpdatePyroAnimation(t_Animation &animation, int index);
		void PyroIncinerateDamage();
		void ClearMap();
		void AbilityStatus();
		void CreateDamage(bool sound = true);
		void UpdateSelector();
		void SelectorWithCharacters();
		void SelectorWithSquares();
		void UpdatePhantomSelector();
		void MultiSelectorWithCharacter();
		void AllSelectorUpdate();
		void UpdateMisses();
		void UpdateRotate(int index);
		void HandleDamageVector(std::vector<t_HitReturn> &ret);
		bool CheckForPhantomKnight();

	public:
		EffectUpdater effectUpdater;
		bool inMotion = false;
		bool active = false;
		bool marking = false;
		void SetAbility(t_Ability *ability, Character *character);
		void SetMap() {groundColoring.SetMap();};
		void Upadte();
		void Clear();
		void CreateOpportunityDamage(Character *damager, Character *target);
		void CreateMiss(Character *damager, Character *target);
};

#endif
