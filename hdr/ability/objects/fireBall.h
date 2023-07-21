
#ifndef FIRE_BALL_H
# define FIRE_BALL_H

# include "../../ab.h"

class FireBall
{
	private:
		SDL_Point goal;
		SDL_FPoint direction;
		Sprite *sprite;
		int counter = 0;
		void GetGoal(SDL_Point target, bool missing);
		void GetMissingGoal(SDL_Point target);
		void RotateDirection();
		void MoveFireBall();
		bool AtTarget();
		bool missing;
	public:
		bool destroy = false;
		FireBall(Character *character, SDL_Point target, bool goingToMiss);
		~FireBall() {Destroy();};
		void Update();
		void Destroy();
};

#endif
