
#ifndef ACID_BOMB_ANIM_H
# define ACID_BOMB_ANIM_H

# include "../../ab.h"

class AcidBombAnim : public AbBase
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
		float angleAddition = 15.0f;
	public:
		bool done = false;
		bool createDamage = false;
		AcidBombAnim(Character *character, SDL_Point target, t_Ability *ability);
		~AcidBombAnim() {Destroy();};
		void Update();
		void Destroy();
};

#endif
