
#ifndef SUPPLY_H
# define SUPPLY_H

# include "../../ab.h"

class Supply
{
	private:
		Character *character;
		ToolBox *box;
		CharacterMover *mover;
		void GetToolBox(SDL_Point target);
	public:
		bool done = false;
		Supply(Character *character, SDL_Point target);
		~Supply() {Destroy();};
		void Update();
		void Destroy();
};

#endif
