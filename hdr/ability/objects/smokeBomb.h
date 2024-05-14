
#ifndef SMOKE_BOMB_H
# define SMOKE_BOMB_H

# include "../../ab.h"

class SmokeBomb : AbBase
{
	private:
		float rotation = 0.0f;
		float rotationAdd = 28.0f;
		Sprite *granade = NULL;
		SDL_Point target;
		SDL_Point start;
		SDL_Point highPoint;
		SDL_FPoint direction;
		bool CheckIfNextTo(SDL_Point start, SDL_Point target);
		bool MoveSmoke();
		void Finale();
		int counter = 0;
	public:
		bool destroy = false;
		bool setEffect = false;
		SmokeBomb(SDL_Point start, SDL_Point target);
		~SmokeBomb() {Destroy();};
		void Update();
		void Destroy();
};

#endif
