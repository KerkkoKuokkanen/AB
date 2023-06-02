
#ifndef BAR_H
# define BAR_H

# include "../ab.h"

class Bar
{
	private:
		Sprite *backGround;
		Sprite *bar;
		Sprite *filler;
		SDL_Rect sRect = {0, 0, 800, 40};
	public:
		Bar(SDL_Rect dest);
		void Update(int max, int curr, Uint8 r, Uint8 g, Uint8 b);
		void Deactivate();
		void Activate();
		void Destroy();
};

#endif
