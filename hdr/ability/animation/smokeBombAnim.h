
#ifndef SMOKE_BOMB_ANIM
# define SMOKE_BOMB_ANIM

# include "../../ab.h"

class SmokeBombAnim
{
	private:
		Character *character;
		CharacterMover *mover;
		Sprite *trail;
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
		void Update();
		void Destroy();
};

#endif
