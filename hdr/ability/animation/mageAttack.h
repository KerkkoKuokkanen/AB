
#ifndef MAGE_ATTACK_H
# define MAGE_ATTACK_H

# include "../../ab.h"

class MageAttack : public AbBase
{
	private:
		Character *character;
		Sprite *light1 = NULL;
		Sprite *light2 = NULL;
		int counter = 0;
		void CreateLight();
		void UpdateLight();
	public:
		bool createEffect = false;
		bool done = false;
		MageAttack(Character *character);
		~MageAttack() {Destroy();};
		void Update();
		void Destroy();
};

#endif
