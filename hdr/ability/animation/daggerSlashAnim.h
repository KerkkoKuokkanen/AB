
#ifndef DAGGER_SLASH_ANIM
# define DAGGER_SLASH_ANIM

# include "../../ab.h"

class DaggerSlashAnim
{
	private:
		SDL_Point target;
		Character *character;
		CharacterMover *mover;
		Sprite *daggerTrail;
		Vector GetDirection();
		void CreateTrail();
		void UpdateTrail();
		int counter = 0;
	public:
		bool createDamage = false;
		bool done = false;
		DaggerSlashAnim(Character *character, SDL_Point target);
		void Update();
		void Destroy();
};

#endif
