
#ifndef HAMMER_SMACK_H
# define HAMMER_SMACK_H

# include "../../ab.h"

class HammerSmack
{
	private:
		CharacterMover *mover = NULL;
		Character *character = NULL;
		Character *target = NULL;
		Sprite *trail = NULL;
		Vector GetDirection();
		int counter = 0;
	public:
		bool done = false;
		bool damage = false;
		HammerSmack(Character *character, Character *target);
		~HammerSmack() {Destroy();};
		void Update();
		void Destroy();
};

#endif
