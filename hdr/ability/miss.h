
#ifndef MISS_H
# define MISS_H

# include "../ab.h"

class MISS
{
	private:
		bool left;
		Sprite *miss;
		int counter;
		SDL_FPoint direction;
		float dirMulti;
		int alpha = 255;
		void ScaleMiss();
		void MoveMiss();
		void AlphaScale();
	public:
		bool done = false;
		MISS(Vector place, bool sound, bool left = false);
		~MISS() {Destroy();};
		void Update();
		void Destroy();
};

#endif
