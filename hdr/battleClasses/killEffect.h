
#ifndef KILL_EFFECT_H
# define KILL_EFFECT_H

# include "../ab.h"

class KillEffect
{
	private:
		Sprite *character = NULL;
		Sprite *stand = NULL;
		SDL_Rect sRect;
		SDL_Surface *sur;
		int counter = 0;
		int iterAmount = 0;
		int heightAmount = 0;
		void ManageSrect();
		void ManageParticles(int start, int end);
		int partCounter = 0;
		int partCount = 0;
	public:
		bool done = false;
		KillEffect(SDL_Surface *sur, Sprite *character, Sprite *stand);
		~KillEffect() {Destroy();};
		void Update();
		void Destroy();
};

#endif
