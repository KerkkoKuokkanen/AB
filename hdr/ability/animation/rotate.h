
#ifndef ROTATE_H
# define ROTATE_H

# include "../../ab.h"

class Rotate : public AbBase
{
	private:
		Character *character;
		Character *target;
		SDL_Point characterTarget;
		SDL_Point targetTarget;
		SDL_FPoint cOgPos;
		SDL_FPoint tOgPos;
		SDL_FPoint cNewPos;
		SDL_FPoint tNewPos;
		SDL_FPoint cHighPoint;
		SDL_FPoint tHighPoint;
		float cUnit;
		float tUnit;
		void ManageIterator();
		Vector GetCharacterWithIterator();
		Vector GetTargetWithIterator();
		int counter = 0;
	public:
		bool done = false;
		Rotate(Character *character, Character *target);
		~Rotate() {Destroy();};
		void Update();
		void Destroy();
};

#endif
