
#ifndef SMOKE_BOMB_ANIM
# define SMOKE_BOMB_ANIM

# include "../../ab.h"

class SmokeBombAnim : AbBase
{
	private:
		Character *character;
		CharacterMover *mover = NULL;
		Sprite *trail = NULL;
		SDL_Point pos;
		void AnimationDone();
		int counter = 0;
		void SetThrowText();
		void RemoveAnimText();
		int alpha = 255;
	public:
		bool active = true;
		bool timeForAbility = false;
		SmokeBombAnim(Character *character, SDL_Point pos);
		~SmokeBombAnim() {Destroy();};
		void Update();
		void Destroy();
};

#endif
