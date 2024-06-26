
#ifndef PICK_UP_TOOL_BOX_H
# define PICK_UP_TOOL_BOX_H

# include "../../ab.h"

class PickUpTools : public AbBase
{
	private:
		Character *character;
		ToolBox *target;
		CharacterMover *mover = NULL;
		bool gotTheBox(SDL_Point pos);
		void GetToolBox();
		SDL_Point targ = {0, 0};
	public:
		bool done = false;
		PickUpTools(Character *character, SDL_Point targ);
		~PickUpTools() {Destroy();};
		ToolBox *GetToolBoxPointer() {return(target);};
		void Update();
		void Destroy();
};

#endif
