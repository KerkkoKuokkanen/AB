
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
		std::vector<std::vector<int>> toolMap;	//remember to clear
		std::vector<Sprite*> moveIndicators;
		std::vector<Sprite*> moveLines;
		void MoveInit(SDL_Renderer *rend);
		std::vector<t_SpriteData> tiles;
		std::vector<std::vector<Sprite>> sprites;	//remember to clear
		unsigned int layer;
		void CreateTile(std::vector<std::vector<t_GMU>> &map, int i, int j, int xStart, int yStart, bool other);
		int GetSprite(std::vector<std::vector<t_GMU>> &map, int i, int j, int iter, bool other);
		int maxHeight, minHeight;
		int currentHeight;
		Uint8 alpha = 35;
		void ChangeUp();
		void ChangeDown();
		std::vector<t_Troop> characters;	//remember to clear
		void PlaceCharacter(SDL_Point &position, t_Troop &character);
		void SetMovables(Character *character);
		void ClearMovables();
		void IterMapMovables(SDL_Point pos, int moves, int cMoves);
		void ColorFade(Sprite *sprite, float fadeIter);
		bool BlockMouseHover(SDL_Point &position);
		bool HoverOverCheck(SDL_Point ogPos);
		bool CheckOverPositions(std::vector<SDL_Point> &positions, SDL_Point og);
		void IterBlocks();
		bool MarkBlock(SDL_Point position);
		void CheckMarkedBlocks(std::vector<SDL_Point> &marked);
		void PlaceMarker();
		void MarkerControl(SDL_Point cPos, SDL_Point mPos);
		void ResetIndicators();
	public:
		std::vector<std::vector<t_GMU>> map;	//remember to clear
		BattleGround(unsigned int layer, SDL_Renderer *rend);
		void CreateBattleGround(std::vector<std::vector<t_GMU>> &map);
		void CreateMap();
		void ChangeMapHeight(bool down);
		void StartBattle(std::vector<Character> &characters, std::vector<SDL_Point> &mapPos);
		void Update();
};

#endif