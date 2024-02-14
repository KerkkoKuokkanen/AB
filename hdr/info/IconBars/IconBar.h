
#ifndef ICON_BAR_H
# define ICON_BAR_H

# include "../../ab.h"

class IconBar
{
	private:
		IconHealth *bars[2] = {NULL, NULL};
		Character *target;
		Sprite *iconBlock;
		Sprite *backGround;
		Sprite *CrossSprites[2] = {NULL, NULL};
		SDL_Rect CrossigRects[2] = {{0, 0, 0, 64}, {64, 0, 0, 64}};
		int slot = 0;
		int counter = 0;
		bool crossing = false;
		void UpdateCrossing();
		void CreateCrosses();
	public:
		bool done = false;
		IconBar(Character *target, int slot, int aStart, int a, int hStart, int h);
		~IconBar() {Destroy();};
		Character *CheckCharacter() {return (target);};
		int GetSlot() {return (slot);};
		void RePosition(int slot);
		void Update();
		void Destroy();
};

#endif
