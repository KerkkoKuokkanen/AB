
#ifndef BIG_THUG_STRIKE_H
# define BIG_THUG_STRIKE_H

# include "../../ab.h"

class BigThugStrike : public AbBase
{
	private:
		Character *character = NULL;
		Character *target = NULL;
		SpriteMover *mover = NULL;
		Sprite *trail = NULL;
		int counter = 0;
		int orderDiff = 0;
		SDL_Point destDims = {0, 0};
		void UpdateTrail(int ret);
		void CreateTrail();
	public:
		bool done = false;
		bool createDamage = false;
		BigThugStrike(Character *character, Character *target);
		~BigThugStrike() {Destroy();};
		void Update();
		void Destroy();
};

#endif
