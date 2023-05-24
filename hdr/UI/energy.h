
#ifndef ENERGY_H
# define ENERGY_H

# include "../ab.h"

class Energy
{
	private:
		Sprite *stand;
		Sprite *energy;
	public:
		Energy();
		void Position(Vector place);
		void Used();
		void TakeBack();
		void Activate();
		void Deactivate();
		void Destroy();
};

#endif
