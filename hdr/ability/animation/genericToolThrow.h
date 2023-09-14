
#ifndef GENERIC_TOOL_THROW_H
# define GENERIC_TOOL_THROW_H

# include "../../ab.h"

class GenericToolThrow
{
	private:
		TileSelector *selector = NULL;
		CharacterMover *mover = NULL;
		Character *character;
		ToolBox *box;
		GroundColoring *coloring;
		void UpdateSelector();
		void UpdateSecondPhase();
		void GetToolBox();
		void SetSelector();
		SDL_Point boxPos = {0, 0};
		SDL_Point boxDest = {0, 0};
		bool secondPhase = false;
		void CreateMover();
	public:
		bool done = false;
		GenericToolThrow(Character *character, SDL_Point target, GroundColoring *coloring);
		~GenericToolThrow() {Destroy();};
		void Update();
		void Destroy();
};

#endif
