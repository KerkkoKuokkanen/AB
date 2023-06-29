
#ifndef DAGGER_H
# define DAGGER_H

# include "../../ab.h"

class Dagger
{
	private:
		Character *character;
		Character *enemy;
		SDL_FPoint direction;
		SDL_FPoint target;
		int destroyCounter = 100;
		bool missing = false;
		SDL_FPoint GetTarget(bool goingToHit, Character *enemy);
		void CreateDamage();
		bool TargetMet();
		bool targetFound = false;
		float speed = 1800.0f;
		void CreateParticles();
	public:
		Sprite *sprite;
		bool remove = false;
		bool createDamage = false;
		Dagger(Character *start, Character *end, bool goingToHit);
		void Update();
		void Destroy();
};

#endif
