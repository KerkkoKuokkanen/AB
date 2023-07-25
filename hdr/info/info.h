
#ifndef INFO_H
# define INFO_H

# include "../ab.h"

class Info
{
	private:
		Character *hovered;
		HoverBars *hoverBars;
		void FindHoveredCharacter();
	public:
		Info();
		~Info() {Destroy();};
		void Update();
		void Destroy();
};

#endif
