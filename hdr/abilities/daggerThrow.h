
#ifndef DAGGER_THROW_H
# define DAGGER_THROW_H

# include "../ab.h"

class DaggerThrow
{
	private:
		int **map;
		Character *character;
		SDL_Point position = {0, 0};
		int range = 13;
		void GetInactivePositions();
		void MarkPosition(SDL_Point pos, int sign);
	public:
		int cost = 3;
		DaggerThrow(Character *character);
		void Update();
		void Destroy();

};

#endif
