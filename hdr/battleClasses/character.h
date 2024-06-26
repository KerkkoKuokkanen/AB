
#ifndef CHARACTER_H
# define CHARACTER_H

# include "../ab.h"

typedef struct s_Stats
{
	int baseDamageLow;
	int baseDamageHigh;
	int speed;
	int maxHealth;
	int health;
	int maxArmor;
	int armor;
	int maxFatigue;
	int fatigue;
	int size;
	int level;
}				t_Stats;

class Character
{
	private:
		std::vector<SDL_Texture*> textures;
		std::vector<SDL_Texture*> stands;
		int width, height;
		SDL_Point coord = {0, 0};
		void CreateCharacterType(int skin);
		void AssignAbilities();
		void ShiftChecker();
		bool animationActive = false;
		void ManageFatigue();
		bool wasTurn = false;
	public:
		SDL_Point topMid = {0, 0};
		int currentTexture = 0;
		int cSing;
		SDL_Point position = {0, 0};
		Sprite *sprite = NULL;
		Sprite *stand = NULL;
		Character(int skin, bool allied = true);
		Character *GetThis() {return (this);};
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
		virtual bool AcceptAbility(int type) {return (true);};
		bool active = true;
		bool hover = false;
		bool clicked = false;
		bool turn = false;
		bool moving = false;
		int moves = 1;
		bool ally = true;
		bool killed = false;
		bool damaged = false;
		t_Stats stats = {22, 34, 1, 100, 100, 50, 50, 80, 0, 3, 1};
		t_StatusEffects statuses = {};
		std::vector<t_Ability> abilities;
};

#endif
