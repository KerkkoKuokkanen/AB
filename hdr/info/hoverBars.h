
#ifndef HOVER_BARS_H
# define HOVER_BARS_H

# include "../ab.h"

class HoverBars
{
	private:
		Bar *health = NULL;
		Bar *armor = NULL;
		Character *target = NULL;
		void PlaceBars();
	public:
		HoverBars();
		~HoverBars() {Destroy();};
		void Update(Character *hovered);
		void Destroy();
};

#endif
