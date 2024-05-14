
#ifndef SMITH_BUFF_H
# define SMITH_BUFF_H

# include "../../ab.h"

class SmithBuff : AbBase
{
	private:
		Character *character;
		Character *target;
		Sprite *lights[2] = {NULL, NULL};
		int counter = 0;
		void CreateLight();
		void UpdateLight();
	public:
		bool done = false;
		bool createBuff = false;
		SmithBuff(Character *character, Character *target);
		~SmithBuff() {Destroy();};
		void Update();
		void Destroy();
};

#endif
