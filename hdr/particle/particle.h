
#ifndef PARTICLE_H
# define PARTICLE_H

# include "../ab.h"

# define GRAVITY_TRUE 1
# define GRAVITY_FALSE 0
# define GRAVITY_OPPOSITE 2

class Particle
{
	private:
		SDL_FPoint dir = {0.0f, 0.0f};
		SDL_FPoint pos = {0.0f, 0.0f};
		float speed = 0.0f;
		int gravity = 0;
		float drag = 1.015f;
	public:
		bool active = false;
		int ogLife = 0;
		int life = 0;
		Sprite *sprite = NULL;
		void init();
		void initWithTexture(SDL_Texture *text, SDL_Rect dest = {0, 0, 200, 200});
		void setPosition(Vector pos);
		void setDirection(Vector dir);
		void setSpeed(float speed);
		void setLifeTime(int lifeTime);
		void setGravity(int sign = 0);
		void setScale(float scale);
		void setTexture(SDL_Texture *text);
		void Activate();
		void SetDrag(float drag);
		void Deactivate();
		void Update();
};

#endif
