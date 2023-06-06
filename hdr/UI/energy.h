
#ifndef ENERGY_H
# define ENERGY_H

# include "../ab.h"

class Energy
{
	private:
		SDL_Surface *sur;
	public:
		Sprite *stand;
		Sprite *energy;
		Energy();
		void Position(Vector place);
		void Used(bool particles = false);
		void TakeBack();
		void Activate();
		void Deactivate();
		void Destroy();
};

#endif
