
#ifndef OW_SPRITE_MOVER_H
# define OW_SPRITE_MOVER_H

# include "../../render/sprite.h"

class OwSpriteMover
{
	private:
		Sprite *sprite = NULL;
		SDL_Point goal = {0, 0};
		SDL_FPoint direction = {0.0f, 0.0f};
		int counter = 0;
	public:
		bool done = false;
		OwSpriteMover(Sprite *sprite, SDL_Point start, SDL_Point end, int time);
		void Update();
};

#endif
