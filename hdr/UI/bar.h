
#ifndef BAR_H
# define BAR_H

# include "../ab.h"

class Bar
{
	private:
		Sprite *backGround;
		Sprite *bar;
		Sprite *filler;
		Sprite *slash;
		Number *stat = NULL;
		Number *maxStat = NULL;
		SDL_Rect sRect = {0, 0, 800, 40};
		int currMax = 0;
		int currCurr = 0;
		void SetBar(int max, int curr);
		void SetNumber();
	public:
		Bar(SDL_Rect dest);
		~Bar() {Destroy();};
		void Update(int max, int curr, Uint8 r, Uint8 g, Uint8 b);
		void Deactivate();
		void Activate();
		void Destroy();
};

#endif
