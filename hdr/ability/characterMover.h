
#ifndef CHARACTER_MOVER_H
# define CHARACTER_MOVER_H

# include "../ab.h"

# define ANIMATION_DONE -1

# define CHARACTER_MOVER_STANDARD_LINEAR_SPEED 80.0f
# define CHARACTER_MOVER_STANDARD_SMOOTH_SPEED 250.0f

class CharacterMover
{
	private:
		Character *character = NULL;
		SDL_FPoint dir;
		float speed;
		int firstTime = 0;
		int totalTime = 0;
		int totalCopy;
		int counter = 0;
		bool linearAlgo;
		void LinearMover();
		void SmoothMover();
		SDL_Rect ogPos;
		bool positioned = false;
	public:
		CharacterMover(Character *character, Vector direction, int firstTime, int secondTime, float speed, bool linear = true);
		int Update();
};

#endif
