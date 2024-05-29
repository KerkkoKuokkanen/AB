
#ifndef OW_SPRITE_MOVER_H
# define OW_SPRITE_MOVER_H

# include "../../render/sprite.h"
# include <vector>

class OwSpriteMover
{
	private:
		std::vector<SDL_Point> travelPoints = {};
		Sprite *sprite = NULL;
		SDL_Point goal = {0, 0};
		int counter = 0;
	public:
		bool done = false;
		OwSpriteMover(Sprite *sprite, SDL_Point start, SDL_Point end, int time);
		void Update();
};

#endif
