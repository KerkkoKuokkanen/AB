
#ifndef CONTROL_ZONE_H
# define CONTROL_ZONE_H

# include "../../ab.h"

class ControlZone
{
	private:
		Character *character;
		SDL_Surface *sur = NULL;
		std::vector<t_Particle> parts = {};
		int counter = 0;
		int partCounter = 0;
		void UpdateColor();
		void ManageParticles();
		void CreateParticles(int start, int goal);
	public:
		bool done = false;
		bool createBuff = false;
		ControlZone(Character *character);
		~ControlZone() {Destroy();};
		void Update();
		void Destroy();
};

#endif
