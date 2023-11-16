
#ifndef BASH_MOVER_H
# define BASH_MOVER_H

# include "../../ab.h"

class BashMover
{
	private:
		Character *attacker;
		Character *target;
		SDL_Point targetPoint;
		ThrowArch *arch = NULL;
		ThrowArch *standArch = NULL;
		SDL_Point tStart = {0, 0};
		SDL_Point GetTargetPoint();
	public:
		bool done = false;
		BashMover(Character *attacker, Character *target, SDL_Point targetLandingPos);
		~BashMover() {Destroy();};
		void Update();
		void Destroy();
};

#endif
