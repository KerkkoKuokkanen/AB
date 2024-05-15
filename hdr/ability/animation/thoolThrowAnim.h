
#ifndef TOOL_THROW_ANIM_H
# define TOOL_THROW_ANIM_H

# include "../../ab.h"

class ToolThrowAnim : public AbBase
{
	private:
		Character *character = NULL;
		SDL_Point target;
		CharacterMover *mover;
		Sprite *trail = NULL;
		ToolBox *box = NULL;
		void CreateTrail();
		void UpdateTrail();
		int counter = 0;
	public:
		bool done = false;
		ToolThrowAnim(Character *character, SDL_Point target);
		~ToolThrowAnim() {Destroy();};
		void Update();
		void Destroy();
};

#endif
