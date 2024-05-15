
#ifndef GENERIC_TOOL_THROW_H
# define GENERIC_TOOL_THROW_H

# include "../../ab.h"

class GenericToolThrow : public AbBase
{
	private:
		CharacterMover *mover = NULL;
		Character *character;
		ToolBox *box;
		void UpdateSecondPhase();
		void GetToolBox();
		SDL_Point boxPos = {0, 0};
		SDL_Point boxDest = {0, 0};
		void CreateMover();
	public:
		bool done = false;
		GenericToolThrow(Character *character, SDL_Point target, SDL_Point goal);
		~GenericToolThrow() {Destroy();};
		void Update();
		void Destroy();
};

#endif
