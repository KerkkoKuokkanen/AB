
#ifndef FLAME_SLASH_H
# define FLAME_SLASH_H

# include "../../ab.h"

class FlameSlash
{
	private:
		Character *character;
		SDL_Point target;
		Sprite *trail;
		CharacterMover *mover;
		int counter = 0;
		Vector GetDirection();
		void UpdateTrail();
		void CreateTrail();
	public:
		bool createDamage = false;
		bool done = false;
		FlameSlash(Character *character, SDL_Point target);
		~FlameSlash() {Destroy();};
		void Update();
		void Destroy();
};

#endif
