
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
	DAGGER_OBJ
};

# define HALF_BLOCK_CHANCE_REDUCE_AMOUNT 1.6f

class Abilities
{
	private:
		std::vector<t_Animation> animations;
		std::vector<t_Object> objects;
		Sprite *block = NULL;
		t_Ability *ability = NULL;
		Character *character = NULL;
		Character *target = NULL;
		Selector *selector = NULL;
		GroundColoring groundColoring;
		DamageCreator damageCreator;
		bool inMotion = false;
		bool blocks = false;
		int chance = 0;
		void SetSelector(t_Ability *ability, Character *character);
		void ActivateAbility(t_Ability *ability, Character *character, Character *target);
		void AnimationUpdater();
		void UpdateSpecificAnimation(t_Animation &animation, int index);
		void ObjectUpdater();
		void UpdateSpecificObject(t_Object &object, int index);
		void ClearMap();
		void AbilityStatus();
		Vector GetDirection();
		void CreateDamage();
		void SetBlockSpriteAndChance(SDL_Point pos);
		void SetBlockSprite(SDL_Point pos, int size);
		void SetUpBlock(Character *target);
		int CheckBlock(Character *target);
		void GetChance(Character *target);
		void ChanceFromStats(Character *target);
		void BlockUpdate();
		void RangedTargetCheck();
		Character *FindBlocker();
	public:
		bool active = false;
		void SetAbility(t_Ability *ability, Character *character);
		void SetMap() {groundColoring.SetMap();};
		void Upadte();
		void Clear();
};

#endif
