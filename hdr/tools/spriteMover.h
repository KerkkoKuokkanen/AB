
#ifndef SPRITE_MOVER_H
# define SPRITE_MOVER_H

# include "../ab.h"

class SpriteMover
{
	private:
		Sprite *sprite;
		SDL_FPoint dir;
		int time;
		float speed;
		int counter = 0;
		SDL_Point startPosition;
		void MoveSprite();
		int half = 0;
	public:
		SpriteMover(Sprite *sprite, Vector direction, int time, float speed);
		~SpriteMover() {Destroy();};
		int Update();
		void Destroy();
};

#endif
