
#ifndef LION_SMACK_ANIM_H
# define LION_SMACK_ANIM_H

# include "../../ab.h"

class LionSmack : AbBase
{
	private:
		Character *character;
		SDL_Point target;
		CharacterMover *mover = NULL;
		Sprite *trail = NULL;
		Vector GetDirection();
		void CreateTrail();
		void UpdateTrail(int ret);
	public:
		bool createDamage = false;
		bool done = false;
		LionSmack(Character *character, SDL_Point target);
		~LionSmack() {Destroy();};
		void Update();
		void Destroy();
};

#endif
