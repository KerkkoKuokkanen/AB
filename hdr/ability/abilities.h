
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

class Abilities
{
	private:
		std::vector<t_Animation> animations;
		std::vector<t_Object> objects;
		t_Ability *ability = NULL;
		Character *character = NULL;
		Character *target = NULL;
		Selector *selector = NULL;
		GroundColoring groundColoring;
		DamageCreator damageCreator;
		bool inMotion = false;
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
	public:
		bool active = false;
		void SetAbility(t_Ability *ability, Character *character);
		void SetMap() {groundColoring.SetMap();};
		void Upadte();
		void Clear();
};

#endif
