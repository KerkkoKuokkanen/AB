
#ifndef WITCH_ANIMATION_H
# define WITCH_ANIMATION_H

# include "../../ab.h"

namespace WitchAnimationType
{
	enum {
		GREEN,
		BLUE,
		RED
	};
};

class WitchAnimation
{
	private:
		Character *character;
		Sprite *glow = NULL;
		Sprite *aura[2] = {NULL, NULL};
		void GetHandGlowSprite();
		int intensity = 0;
		int colorType = 0;
		int counter = 0;
		void UpdateAuraAlpha();
		void CreateParticles();
		SDL_Point GetPartPos();
		Color GetPartColor();
	public:
		bool done = false;
		WitchAnimation(Character *character, int type, int intensity);
		~WitchAnimation() {Destroy();};
		void Update();
		void Destroy();
};

#endif
