
#ifndef ACID_BOMB_BLAST_H
# define ACID_BOMB_BLAST_H

# include "../ab.h"

class AcidBombBlast
{
	private:
		unsigned int variation;
		SDL_Point position;
		int counter = 0;
		int particleAmount = 20;
		int adder = 40;
		int defLife = 20;
		int max = 100;
		void CreateParticles();
		void GetParticleAmount();
	public:
		bool done = false;
		AcidBombBlast(SDL_Point position, unsigned int variation);
		~AcidBombBlast() {Destroy();};
		void Update();
		void Destroy();

};

#endif
