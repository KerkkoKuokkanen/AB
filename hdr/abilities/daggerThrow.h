
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
		void OverEnemy(Character *enemy);
		Vector GetDirection(Character *enemy);
	public:
		bool thrown = false;
		int cost;
		DaggerThrow(Character *character, int cost);
		void Update();
		void Destroy();

};

#endif
