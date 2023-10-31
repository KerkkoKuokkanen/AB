
#ifndef SLOWED_EFFECT_H
# define SLOWED_EFFECT_H

# include "../ab.h"

class SlowedEffect
{
	private:
		Character *character;
		int counter = 0;
		void UpdateColor();
		void CreateParticles();
	public:
		bool done = false;
		SlowedEffect(Character *target);
		~SlowedEffect() {Destroy();};
		void Update();
		void Destroy();
};

#endif
