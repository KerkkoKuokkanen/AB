
#ifndef BAR_H
# define BAR_H

# include "../ab.h"

class Bar
{
	private:
		Sprite *backGround;
		Sprite *bar;
		Sprite *filler;
	public:
		Bar(SDL_Rect dest);
		void Update(int max, int curr, Uint8 r, Uint8 g, Uint8 b);
		void Deactivate();
		void Activate();
		void Destroy();
};

#endif
