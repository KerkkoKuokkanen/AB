
#ifndef CHARACTER_H
# define CHARACTER_H

# include "../ab.h"

typedef struct s_Stats
{
	int speed;
	int maxHealth;
	int health;
	int maxArmor;
	int armor;
}				t_Stats;

class Character
{
	private:
		std::vector<SDL_Texture*> textures;
		std::vector<SDL_Texture*> stands;
		int width, height;
		SDL_Point coord = {0, 0};
		void CreateCharacterType(int skin);
		void ShiftChecker();
		bool animationActive = false;
	public:
		int currentTexture = 0;
		int cSing;
		SDL_Point position = {0, 0};
		Sprite *sprite;
		Sprite *stand;
		Character(int skin, bool allied = true);
		void FindPosition();
		void Destroy();
		void AddToRender();
		void Update();
		void DeleteCharacter();
		int getWidth() {return (width);};
		int getHeight() {return (height);};
		void setCoord(SDL_Point &coord);
		void setAnimationActive(bool set) {animationActive = set;};
		SDL_Point &getCoord();
		void Position(Vector to);
		void Move(Vector amount);
		bool active = true;
		bool hover = false;
		bool clicked = false;
		bool turn = false;
		bool moving = false;
		int moves = 1;
		bool ally = true;
		bool killed = false;
		t_Stats stats = {1, 100, 100, 50, 50};
		std::vector<t_Ability> abilities = {{DAGGER_THROW, 0, 80, NULL}, {SMOKE_BOMB, 0, 200, NULL}};
};

#endif
