
#ifndef TILE_BLOCK_H
# define TILE_BLOCK_H

# include "../../render/sprite.h"

class TileBlock
{
	private:
		Sprite *sprite;
		SDL_Rect sRect;
	public:
		TileBlock(SDL_Texture *text, SDL_Rect sRect);
		~TileBlock() {Destroy();};
		void Destroy();
};

#endif
