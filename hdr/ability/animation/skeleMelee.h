
#ifndef SKELE_MELEE_H
# define SKELE_MELEE_H

# include "../../ab.h"

class SkeleMeleeAnim
{
	private:
		Character *character = NULL;
		Character *target = NULL;
		SpriteMover *mover = NULL;
		void UpdateSprite(int ret);
		int orderDiff = 0;
	public:
		bool done = false;
		bool createDamage = false;
		SkeleMeleeAnim(Character *character, Character *target);
		~SkeleMeleeAnim() {Destroy();};
		void Update();
		void Destroy();
};

#endif
