
#ifndef SUPPLY_ALLY_H
# define SUPPLY_ALLY_H

# include "../../ab.h"

class SupplyAlly
{
	private:
		CharacterMover *mover;
		Character *character = NULL;
	public:
		Character *target = NULL;
		bool done = false;
		bool removeFat = false;
		SupplyAlly(Character *character, Character *target);
		~SupplyAlly() {Destroy();};
		void Update();
		void Destroy();
};

#endif
