
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
		void CheckIfDone();
		bool turn = true;
		int time = 0;
		Character *character = NULL;
		SDL_Point pos;
	public:
		bool done = false;
		SmokeEffect(Character *character, t_Ability *ability, SDL_Point pos);
		~SmokeEffect() {Destroy();};
		int getTime() {return(time);};
		void Update();
		void Destroy();
};

#endif
