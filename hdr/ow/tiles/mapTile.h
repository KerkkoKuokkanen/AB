
#ifndef MAP_TILE_H
# define MAP_TILE_H

#define DIMENTIONS 3200

# include "../../render/sprite.h"

class MapTile
{
	private:
		Sprite *sprite = NULL;
		Sprite *outline = NULL;
		SDL_Rect sourceRect;
		bool active = true;
	public:
		MapTile(SDL_Texture *text, SDL_Rect sRect, SDL_Point pos);
		~MapTile() {Destroy();};
		void Deactivate();
		void Activate();
		void IsCurrentPos();
		bool GetStatus() {return (active);};
		void Update();
		void Destroy();
};

#endif
