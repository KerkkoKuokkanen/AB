
#ifndef LIGHTNING_BOLT_H
# define LIGHTNING_BOLT_H

# include "../../ab.h"

class LightningBolt : public AbBase
{
	private:
		SDL_Point target;
		Sprite *sprite = NULL;
		int counter = 0;
		void UpdateAlpha();
		void MoveLightning();
		void CreateParticles();
	public:
		bool createDamage = false;
		bool done = false;
		LightningBolt(SDL_Point target);
		~LightningBolt() {Destroy();};
		void Update();
		void Destroy();
};

#endif
