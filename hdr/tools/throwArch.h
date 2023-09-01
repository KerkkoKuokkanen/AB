
#ifndef THROW_ARCH_H
# define THROW_ARCH_H

# include "../ab.h"

class ThrowArch
{
	private:
		Sprite *sprite;
		SDL_Point start;
		SDL_Point end;
		SDL_Point midPoint;
		SDL_FPoint direction;
		SDL_FPoint midDir;
		float max;
		float speed;
		float midMag;
		float totalMag;
		float angleMulti = 1.0f;
		void CalculateMidPoint();
		float getMulti();
		SDL_FPoint MoveUp(SDL_FPoint pos);
		SDL_FPoint GetPosition();
		void MoveSprite(SDL_FPoint pos);
		bool CheckIfDone(SDL_FPoint pos);
		int counter = 0;
		int ogOrder = 0;
	public:
		bool done = false;
		ThrowArch(Sprite *sprite, SDL_Point start, SDL_Point end, float maxDist, float speed);
		~ThrowArch() {Destroy();};
		void Update();
		void Destroy();
};

#endif
