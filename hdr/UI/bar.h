
#ifndef BAR_H
# define BAR_H

# include "../ab.h"

class Bar
{
	private:
		Sprite *backGround;
		Sprite *bar;
		Sprite *filler;
		Sprite *reduce;
		Sprite *slash = NULL;
		Number *stat = NULL;
		Number *maxStat = NULL;
		SDL_Rect sRect = {0, 0, 800, 40};
		SDL_Rect rSRect = {0, 0, 800, 40};
		int currMax = 0;
		int currCurr = 0;
		void SetBar(int max, int curr);
		void SetNumber();
		void ModBars(Character *target, bool health);
		void ManageReduce();
		bool numbers;
		bool healthDown = false;
		bool staticSprite;
		bool colorSet = false;
		Character *target = NULL;
	public:
		Bar(SDL_Rect dest, bool numbers, bool staticSprite = true);
		~Bar() {Destroy();};
		void SetColor(Uint8 r, Uint8 g, Uint8 b);
		void Position(SDL_Point place);
		void Update(Character *target, bool health);
		void Deactivate();
		void Activate();
		void Destroy();
};

#endif
