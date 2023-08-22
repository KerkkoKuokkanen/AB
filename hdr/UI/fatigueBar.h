
#ifndef FATIGUE_BAR_H
# define FATIGUE_BAR_H

# include "../ab.h"

class FatigueBar
{
	private:
		Sprite *bar = NULL;
		Sprite *backGround = NULL;
		Sprite *filler = NULL;
		Sprite *shower = NULL;
		Number *stat = NULL;
		Number *maxStat = NULL;
		SDL_Rect sRect = {0, 0, 800, 40};
		SDL_Rect rSRect = {0, 0, 800, 40};
		int currentFatigue = 0;
		int maxFatigue = 0;
		bool staticSprite = true;
		int layer;
		int currStat = -4444;
		int currMax = -4444;
		int numSize = 800;
		bool fatigueCalled = false;
		int fatigueIter = 0;
		int last = 0;
		void Setbar(Character *character);
		void SetNumber(Character *character);
		void CheckFatigueCalled();
	public:
		Sprite *slash = NULL;
		SDL_Point leftNumberOffset = {0, 0};
		SDL_Point rightNumberOffset = {0, 0};
		FatigueBar(SDL_Rect dest, bool staticSprite = true);
		~FatigueBar() {Destroy();};
		void SmallerNumbers() {numSize = 650;};
		void ShowFatigue(int cost);
		void Deactivate();
		void Activate();
		void Update(Character *character);
		void Destroy();
};

#endif
