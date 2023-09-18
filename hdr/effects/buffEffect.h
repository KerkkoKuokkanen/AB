
#ifndef BUFF_EFFECT_H
# define BUFF_EFFECT_H

# include "../ab.h"

class BuffEffect
{
	private:
		Character *target;
		int counter = 0;
	public:
		BuffEffect(Character *target, bool buff);
		~BuffEffect() {Destroy();};
		void Update();
		void Destroy();
};

#endif
