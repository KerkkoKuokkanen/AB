
#ifndef ENERGY_H
# define ENERGY_H

# include "../ab.h"

class Energy
{
	public:
		Sprite *stand;
		Sprite *energy;
		Energy();
		void Position(Vector place);
		void Used();
		void TakeBack();
		void Activate();
		void Deactivate();
		void Destroy();
};

#endif
