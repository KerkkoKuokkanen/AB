
#ifndef TOXIN_BUFF_H
# define TOXIN_BUFF_H

# include "../../ab.h"

class ToxinBuff
{
	private:
		Character *character;
		std::vector<t_Particle> parts = {};
		SDL_Surface *sur = NULL;
		int counter = 0;
		int partCounter = 0;
		void ToxinBuffColorChange();
		void CreateParticles(int y, int yTarg);
	public:
		bool done = false;
		bool addStatus = false;
		ToxinBuff(Character *character);
		~ToxinBuff() {Destroy();};
		void Update();
		void Destroy();

};

#endif
