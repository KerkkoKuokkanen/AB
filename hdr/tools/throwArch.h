
#ifndef THROW_ARCH_H
# define THROW_ARCH_H

# include "../ab.h"

class ThrowArch
{
	private:
		Sprite *sprite;
		SDL_Point start;
		SDL_Point end;
		SDL_FPoint direction;
		SDL_FPoint addDir;
		SDL_FPoint maxDir;
		SDL_FPoint position;
		float max;
		float speed;
		float magnitude;
		float directionalMulti = 1.0f;
		int counter = 0;
		int ogOrder = 0;
		void GetDirection();
		void GetDirectionMulti();
		void UpdatePosition();
		void PlaceSprite();
		bool CheckIfDone();
		float goalMagnitude = 500.0f;
	public:
		bool done = false;
		ThrowArch(Sprite *sprite, SDL_Point start, SDL_Point end, float maxDist, float speed);
		~ThrowArch() {Destroy();};
		void Update();
		void SetGoalMagnitude(float mag) {goalMagnitude = mag;};
		void Destroy();
};

#endif
