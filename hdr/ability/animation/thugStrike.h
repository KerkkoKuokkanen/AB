
#ifndef THUG_STRIKE_H
# define THUG_STRIKE_H

# include "../../ab.h"

class ThugStrike
{
	private:
		Character *character = NULL;
		SpriteMover *mover = NULL;
		int orderAdd = 0;
	public:
		bool done = false;
		bool createDamage = false;
		ThugStrike(Character *character, Character *target);
		~ThugStrike() {Destroy();};
		void Update();
		void Destroy();
};

#endif
