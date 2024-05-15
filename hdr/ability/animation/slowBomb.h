
#ifndef SLOW_BOMB_H
# define SLOW_BOMB_H

# include "../../ab.h"

class SlowBomb : public AbBase
{
	private:
		ThrowArch *arch = NULL;
		CharacterMover *mover = NULL;
		Character *character;
		Sprite *bomb = NULL;
		SDL_Point target;
		Sprite *trail = NULL;
		t_Ability *ability;
		void StartThrow();
		void UpdateTrail(int ret);
		void UpdateMover();
		void UpdateBomb();
		bool CheckIfDone();
		void CreateParticles();
		bool bombCreated = false;
		bool damageCreated = false;
		int counter = 0;
		float angleAddition = 15.0f;
	public:
		bool done = false;
		bool createDamage = false;
		SlowBomb(Character *character, SDL_Point target, t_Ability *ability);
		~SlowBomb() {Destroy();};
		void Update();
		void Destroy();
};

#endif
