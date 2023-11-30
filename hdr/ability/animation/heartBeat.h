
#ifndef HEART_BEAT_H
# define HEART_BEAT_H

# include "../../ab.h"

class HeartBeat
{
	private:
		Character *character = NULL;
		Character *target = NULL;
		Sprite *outline = NULL;
		Sprite *backGround = NULL;
		Sprite *beat = NULL;
		WitchAnimation *anim = NULL;
		SDL_Rect srect = {0, 0, 0, 0};
		void UpdateOutline();
		void ManagePulse();
		void CreatePulse();
		void ManagePulseMove();
		void ManageSize();
		int srectUnit = 0;
		int counter = 0;
		int conterSave = (-1);
	public:
		bool createEffect = false;
		bool done = false;;
		HeartBeat(Character *character, Character *target);
		~HeartBeat() {Destroy();};
		void Update();
		void Destroy();
};

#endif
