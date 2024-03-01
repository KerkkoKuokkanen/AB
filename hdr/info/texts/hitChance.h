
#ifndef HIT_CHANCE_H
# define HIT_CHANCE_H

# include "../../ab.h"

class HitChanceBubble
{
	private:
		TextBubble *bubble = NULL;
		int counter = 0;
		int currAbility = 0;
		Character *currHover = NULL;
		void Deleting();
		void CreateBubble();
	public:
		void Update(Character *hovered);
};

#endif
