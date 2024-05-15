
#ifndef ROCK_FALL_H
# define ROCK_FALL_H

# include "../../ab.h"

class RockFall : public AbBase
{
	private:
		Sprite *sprite = NULL;
		int counter = 0;
		void UpdateAlpha();
		void MoveRocks();
		void CreateParticles();
		void UpdateFadeAlpha();
	public:
		SDL_Point target;
		bool done = false;
		bool createDamage = false;
		RockFall(SDL_Point target);
		~RockFall() {Destroy();};
		void Update();
		void Destroy();
};

#endif
