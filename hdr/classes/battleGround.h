
#ifndef BATTLE_GROUND_H
# define BATTLE_GROUND_H

# include "../ab.h"

typedef struct s_SpriteConstructor
{
	SDL_Texture *texture;
	SDL_Rect	srect;
}				t_SpriteData;

typedef struct s_GroundMapUnit
{
	int tile;
	int height;
}				t_GMU;

class BattleGround {
	private:
		std::vector<t_SpriteData> tiles;
		std::vector<Sprite> sprites;
		unsigned int layer;
		void CreateTile(std::vector<std::vector<t_GMU>> &map, int i, int j, int xStart, int yStart, bool other);
		int GetSprite(std::vector<std::vector<t_GMU>> &map, int i, int j, int iter, bool other);
	public:
		BattleGround(unsigned int layer, SDL_Renderer *rend);
		void CreateBattleGround(std::vector<std::vector<t_GMU>> &map);
};

#endif
