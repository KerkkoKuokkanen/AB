
#ifndef MAP_TILE_H
# define MAP_TILE_H

# include "../../render/sprite.h"

class MapTile
{
	private:
		Sprite *sprite = NULL;
		Sprite *outline = NULL;
		SDL_Rect sourceRect;
	public:
		MapTile(SDL_Texture *text, SDL_Rect sRect, SDL_Point pos);
		~MapTile() {Destroy();};
		void Update();
		void Destroy();
};

#endif
