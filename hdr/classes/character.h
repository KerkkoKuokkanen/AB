
#ifndef CHARACTER_H
# define CHARACTER_H

# include "../ab.h"

typedef struct s_Stats
{
	int speed;
}				t_Stats;

class Character
{
	private:
		std::vector<SDL_Texture*> textures;
		int idleCounter = 0;
		int currentTexture = 0;
		int width, height;
		SDL_Point coord = {0, 0};
		void CreateCharacterType(int skin);
	public:
		int cSing;
		Sprite *sprite;
		Character(int skin, bool allied = true);
		void AddToRender();
		void Update();
		void DeleteCharacter();
		int getWidth() {return (width);};
		int getHeight() {return (height);};
		void setCoord(SDL_Point &coord);
		SDL_Point &getCoord();
		void Position(Vector to);
		void Move(Vector amount);
		bool hover = false;
		bool clicked = false;
		bool turn = false;
		bool moving = false;
		int moves = 10;
		bool ally = true;
		t_Stats stats = {1};
};

#endif
