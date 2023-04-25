
#ifndef BATTLE_GROUND_H
# define BATTLE_GROUND_H

# include "../ab.h"

typedef struct s_SpriteConstructor
{
	SDL_Texture *texture;
	SDL_Rect	srect;
}				t_SpriteData;

typedef struct s_Troop
{
	Character *character;
	bool clicked;
	SDL_Point pos;
}				t_Troop;

class BattleGround {
	private:
		std::vector<t_SpriteData> tiles;
		std::vector<std::vector<Sprite>> sprites;
		unsigned int layer;
		void CreateTile(std::vector<std::vector<t_GMU>> &map, int i, int j, int xStart, int yStart, bool other);
		int GetSprite(std::vector<std::vector<t_GMU>> &map, int i, int j, int iter, bool other);
		int maxHeight, minHeight;
		int currentHeight;
		Uint8 alpha = 35;
		void ChangeUp();
		void ChangeDown();
		std::vector<t_Troop> characters;
		void PlaceCharacter(SDL_Point &position, t_Troop &character);
		void SetTextureOnHover(int i);
		void MovingUpdate();
		void SetMovables(Character *character);
		void ClearMovables();
		void IterMapMovables(SDL_Point pos, int moves, int cMoves);
	public:
		std::vector<std::vector<t_GMU>> map;
		BattleGround(unsigned int layer, SDL_Renderer *rend);
		void CreateBattleGround(std::vector<std::vector<t_GMU>> &map);
		void CreateMap();
		void ChangeMapHeight(bool down);
		void StartBattle(std::vector<Character> &characters, std::vector<SDL_Point> &mapPos);
		void Update();
};

#endif
