
#ifndef TELE_START_H
# define TELE_START_H

# include "../../ab.h"

class TeleStart : public AbBase
{
	private:
		Character *character = NULL;
		Character *target = NULL;
		WitchAnimation *animation = NULL;
		int counter = 0;
		void UpdateTargetAlpha();
		bool colDone = false;
	public:
		bool createEffect = false;
		bool done = false;
		TeleStart(Character *character, SDL_Point target);
		~TeleStart() {Destroy();};
		void Update();
		void Destroy();
};

#endif
