
#ifndef TURN_ORDER_H
# define TURN_ORDER_H

# include "../ab.h"

class TurnOrder
{
	private:
		std::vector<Character*> character;
		Sprite *banner;
		Sprite *backGround;
	public:
		TurnOrder(std::vector<Character> &characters);
		void Update();
		void Destroy();
};

#endif
