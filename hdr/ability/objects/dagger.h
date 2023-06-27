
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
		int lifeTime = 120;
		bool left = false;
		bool down = false;
		bool missing = false;
		SDL_FPoint GetTarget(int hitChance, Character *enemy);
		void CreateDamage();
		bool TargetMet();
		bool targetFound = false;
		float speed = 1800.0f;
		void CreateParticles();
	public:
		Sprite *sprite;
		bool remove = false;
		bool createDamage = false;
		Dagger(Character *start, Character *end, int hitChance);
		void Update();
		void Destroy();
};

#endif
