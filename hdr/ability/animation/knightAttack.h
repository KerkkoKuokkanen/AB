
#ifndef KNIGHT_ATTACK_H
# define KNIGHT_ATTACK_H

# include "../../ab.h"

class KnightAttack
{
	private:
		Character *character;
		Character *target;
		Sprite *trail = NULL;
		SpriteMover *mover = NULL;
		void CreateTrail();
		void UpdateTrail(int ret);
		SDL_Point destDims;
		int counter = 0;
		int orderDiff = 0;
	public:
		bool done = false;
		bool createDamage = false;
		KnightAttack(Character *character, Character *target);
		~KnightAttack() {Destroy();};
		void Update();
		void Destroy();
};

#endif
