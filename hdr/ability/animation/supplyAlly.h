
#ifndef SUPPLY_ALLY_H
# define SUPPLY_ALLY_H

# include "../../ab.h"

class SupplyAlly : public AbBase
{
	private:
		CharacterMover *mover = NULL;
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
