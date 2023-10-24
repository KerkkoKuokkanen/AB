
#ifndef NAIL_BOMB_H
# define NAIL_BOMB_H

# include "../../ab.h"

class NailBomb
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
		bool bombCreated = false;
		bool damageCreated = false;
		int counter = 0;
	public:
		bool done = false;
		bool createDamage = false;
		NailBomb(Character *character, SDL_Point target, t_Ability *ability);
		~NailBomb() {Destroy();};
		void Update();
		void Destroy();
};

#endif
