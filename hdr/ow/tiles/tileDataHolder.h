
#ifndef TILE_DATA_HOLDER_H
# define TILE_DATA_HOLDER_H

# include "mapTile.h"
# include <vector>

typedef struct s_TileData
{
	int textureType;
	SDL_Rect sRect;
}				t_TileData;

class TileDataHolder
{
	private:
		int range = 12;
		int activeRange = 25;
		SDL_Point position = {0, 0};
		Sprite *mule = NULL;
		std::vector<std::vector<t_TileData>> mapData;
		std::vector<std::vector<MapTile*>> mapTiles;
		std::vector<SDL_Point> broughtTiles;
		bool ValidPosition(SDL_Point pos);
		void BringTiles();
		void UpdateTiles();
	public:
		TileDataHolder(const char *address);
		~TileDataHolder() {Destroy();};
		void SetPosition(SDL_Point pos);
		SDL_Point GetPosition() {return (position);};
		void SetRange(int range) {TileDataHolder::range = range;};
		void Update();
		void Destroy();
};

#endif
