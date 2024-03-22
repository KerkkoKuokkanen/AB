
#ifndef BIG_THUG_BUFF_H
# define BIG_THUG_BUFF_H

# include "../../ab.h"

class BigThugInspire
{
	private:
		Character *character = NULL;
		Sprite *buffLights[2] = {NULL, NULL};
		int counter = 0;
		void ManageAlpha();
	public:
		bool createBuff = false;
		bool done = false;
		BigThugInspire(Character *character);
		~BigThugInspire() {Destroy();};
		void Update();
		void Destroy();
};

#endif
