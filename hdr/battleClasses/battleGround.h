
#ifndef BATTLE_GROUND_H
# define BATTLE_GROUND_H

# include "../ab.h"

# define ALPHA 35

typedef struct s_SpriteConstructor
{
	SDL_Texture *texture;
	SDL_Rect	srect;
}				t_SpriteData;

typedef struct s_Troop
{
	Character *character;
	bool clicked;
}				t_Troop;

typedef struct s_Mover
{
	Character *character;
	std::vector<SDL_Point> path;
	int index;
	int iterator;
}				t_Mover;

class BattleGround {
	private:
		SDL_Texture *moveInd;
		SDL_Texture *lineInd;
		t_Mover movedCharacter = {NULL, {}, 0, 0};
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
		void PlaceCharacter(SDL_Point &position, Character *character);
		void SetMovables(Character *character);
		void ClearMovables();
		void IterMapMovables(SDL_Point pos, int moves, int cMoves, int highLightSign);
		void ColorFade(Sprite *sprite, int sign);
		bool BlockMouseHover(SDL_Point &position);
		bool HoverOverCheck(SDL_Point ogPos);
		bool CheckOverPositions(std::vector<SDL_Point> &positions, SDL_Point og);
		void IterBlocks();
		bool MarkBlock(SDL_Point position);
		void CheckMarkedBlocks(std::vector<SDL_Point> &marked);
		void PlaceMarker();
		void MarkerControl(SDL_Point cPos, SDL_Point mPos);
		void ResetIndicators();
		std::vector<SDL_Point> FindPath(SDL_Point cPos, SDL_Point tPos);
		void TakeMarkerAndPlaceIt(SDL_Point pos);
		void TakeLineAndPlaceIt(SDL_Point startPos, SDL_Point endPos);
		void CreateNewIndicator();
		void CreateNewLine();
		int findLine();
		void setMoved(std::vector<SDL_Point> &path);
		void MoveCharacter();
		Vector GetCharacterCoord(SDL_Point pos, Character *character);
		void FigureOrderingLayer(SDL_Point curr, SDL_Point next);
		Vector ParabolaPosition(Vector pos, Vector highPoint, float unit, float ogX);
		Vector GetPlaceWithIterator(Vector ogPos, Vector newPos, float unit, Vector highPoint, SDL_Point curr, SDL_Point next);
		void MangeIterator(Vector newPos);
		bool NoOtherCharacters();
		bool MovingLeft(SDL_Point curr, SDL_Point next);
		void AddDust(SDL_Point curr, SDL_Point next);
		void CheckBlocked(int i, int j);
	public:
		std::vector<t_Troop> characters;	//remember to clear
		std::vector<std::vector<t_GMU>> map;	//remember to clear
		BattleGround(unsigned int layer, SDL_Renderer *rend);
		SDL_Rect getTileDest(SDL_Point pos);
		void CreateBattleGround(std::vector<std::vector<t_GMU>> &map);
		void CreateMap();
		void ChangeMapHeight(bool down);
		void StartBattle(std::vector<Character> &characters, std::vector<SDL_Point> &mapPos);
		void HighLightBlock(SDL_Point pos, Uint8 r, Uint8 g, Uint8 b);
		void ResetBlockColor(SDL_Point pos);
		void RemoveCharacter(Character *character);
		Sprite *GetSprite(SDL_Point pos);
		void Update();
};

#endif
