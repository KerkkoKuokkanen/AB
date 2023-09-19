
#ifndef BUFF_EFFECT_H
# define BUFF_EFFECT_H

# include "../ab.h"

class BuffEffect
{
	private:
		Character *target;
		SDL_Surface *sur;
		std::vector<t_Particle> parts = {};
		int counter = 0;
		bool buff;
		void UpdateBuff();
		void UpdateDebuff();
		int partCounter = 0;
		void UpdateBuffColor();
		void UpdateDeBuffColor();
		void CreateParticles(int y, int yTarg);
		void ManageParticles();
	public:
		bool done = false;
		BuffEffect(Character *target, bool buff);
		~BuffEffect() {Destroy();};
		void Update();
		void Destroy();
};

#endif
