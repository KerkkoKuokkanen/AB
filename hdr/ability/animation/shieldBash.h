
#ifndef SHIELD_BASH_H
# define SHIELD_BASH_H

# include "../../ab.h"

class ShieldBash : public AbBase
{
	private:
		Character *character;
		Character *target;
		SpriteMover *mover = NULL;
		Sprite *trail = NULL;
		SDL_Point dims;
		int orderDiff = 0;
		int counter = 0;
		void CreateTrail();
		void UpdateTrail(int ret);
	public:
		bool done = false;
		bool createDamage = false;
		ShieldBash(Character *character, Character *target);
		~ShieldBash() {Destroy();};
		void Update();
		void Destroy();
};

#endif
