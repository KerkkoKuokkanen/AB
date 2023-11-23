
#ifndef PICK_UP_TOOL_BOX_H
# define PICK_UP_TOOL_BOX_H

# include "../../ab.h"

class PickUpTools
{
	private:
		Character *character;
		ToolBox *target;
		CharacterMover *mover = NULL;
		bool gotTheBox(SDL_Point pos);
		void GetToolBox();
	public:
		bool done = false;
		PickUpTools(Character *character);
		~PickUpTools() {Destroy();};
		ToolBox *GetToolBoxPointer() {return(target);};
		void Update();
		void Destroy();
};

#endif
