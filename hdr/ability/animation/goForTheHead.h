
#ifndef GO_FOR_THE_HEAD_H
# define GO_FOR_THE_HEAD_H

# include "../../ab.h"

class GoForTheHead
{
	private:
		Character *character;
		Character *target;
		CharacterMover *mover = NULL;
		Sprite *trail = NULL;
		Vector GetDirection();
		void CreateTrail();
		void UpdateTrail(int ret);
		int counter = 0;
	public:
		bool done = false;
		bool createDamage = false;
		GoForTheHead(Character *character, Character *target);
		~GoForTheHead() {Destroy();};
		void Update();
		void Destroy();
};

#endif
