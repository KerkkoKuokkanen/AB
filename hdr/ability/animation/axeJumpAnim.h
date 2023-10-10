
#ifndef AXE_JUMP_ANIM_H
# define AXE_JUMP_ANIM_H

# include "../../ab.h"

class AxeJumpAnim
{
	private:
		Character *character;
		Character *target;
		SDL_Point pos;
		ThrowArch *arch = NULL;
		int counter = 0;
		void StartJump();
		void UpdateJump();
	public:
		bool done = false;
		bool createDamage = false;
		AxeJumpAnim(Character *character, Character *target, SDL_Point pos);
		~AxeJumpAnim() {Destroy();};
		void Update();
		void Destroy();
};

#endif
