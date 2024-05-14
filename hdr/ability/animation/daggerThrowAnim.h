
#ifndef DAGGER_THROW_ANIM_H
# define DAGGER_THROW_ANIM_H

# include "../../ab.h"

# define DAGGER_THROW_ANIMATION_TIME 14

class DaggerThrowAnim : public AbBase
{
	private:
		SDL_FPoint direction;
		Character *character;
		Character *enemy;
		int counter = DAGGER_THROW_ANIMATION_TIME;
		void MoveToEnemy();
		void MoveBack();
		void AnimationDone();
		bool thrown = false;
	public:
		bool active = true;
		bool timeForAbility = false;
		DaggerThrowAnim(Character *character, Character *enemy);
		void Update();
};

#endif
