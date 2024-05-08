
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
		int range = 10;
		SDL_Point position = {0, 0};
		std::vector<std::vector<t_TileData>> mapData;
		std::vector<std::vector<MapTile*>> mapTiles;
		bool ValidPosition(SDL_Point pos);
		void BringTiles();
		void UpdateTiles();
		void SetCamera();
	public:
		TileDataHolder(const char *address);
		~TileDataHolder() {Destroy();};
		void SetPosition(SDL_Point pos) {position = pos;};
		void SetRange(int range) {TileDataHolder::range = range;};
		void Update();
		void Destroy();
};

#endif
