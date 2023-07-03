
#ifndef SMOKE_EFFECT_H
# define SMOKE_EFFECT_H

# include "../../ab.h"

class SmokeEffect
{
	private:
		Sprite *firstSmoke;
		Sprite *secondSmoke;
		SDL_Rect tileDest;
		int orientation = 0;
		void SwitchOrdering();
		SDL_Point pos;
	public:
		SmokeEffect(SDL_Point pos);
		~SmokeEffect() {Destroy();};
		void Update();
		void Destroy();
};

#endif
