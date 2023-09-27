
#ifndef HOST_EFFECT_H
# define HOST_EFFECT_H

# include "../ab.h"

class HostEffect
{
	private:
		Character *character;
		int counter = 0;
		void UpdateColor();
		void CreateParticles();
	public:
		bool done = false;
		HostEffect(Character *target);
		~HostEffect() {Destroy();};
		void Update();
		void Destroy();
};

#endif
