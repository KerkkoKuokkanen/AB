
#ifndef AXE_SLASH_H
# define AXE_SLASH_H

# include "../../ab.h"

class AxeSlash
{
	private:
		Character *character;
		Character *target;
		CharacterMover *mover = NULL;
		Sprite *trail = NULL;
		void CreateTrail();
		void FadeTrail(int ret);
		void SetTextBack();
	public:
		bool done = false;
		bool createDamage = false;
		AxeSlash(Character *character, Character *target);
		~AxeSlash() {Destroy();};
		void Update();
		void Destroy();
};

#endif
