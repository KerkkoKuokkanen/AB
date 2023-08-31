
#ifndef SUPPLY_EFFECT_H
# define SUPPLY_EFFECT_H

# include "../ab.h"

class SupplyEffect
{
	private:
		Character *target;
		std::vector<t_Particle> parts = {};
		SDL_Surface *sur = NULL;
		int counter = 0;
		int partCounter = 0;
		void UpdateColor();
		void CreateParticles(int y, int yTarg);
		void ManageParticles();
	public:
		bool done = false;
		SupplyEffect(Character *target);
		~SupplyEffect() {Destroy();};
		void Update();
		void Destroy();
};

#endif
