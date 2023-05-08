
#ifndef TURN_ORDER_H
# define TURN_ORDER_H

# include "../ab.h"

typedef struct s_Indicator
{
	Sprite *indicator;
	Character *character;
	SDL_Rect *srect;
	float x;
	bool active;
}				t_Indicator;

class TurnOrder
{
	private:
		std::vector<Character*> characters;
		std::vector<t_Indicator> indicators;
		Sprite *banner;
		Sprite *backGround;
		void CreateIndicators();
		void CreateSRect(SDL_Rect *srect, int cSing);
		SDL_Rect CreateDest(int cSing);
		void StartTurn();
		int posCount = 8;
		bool turnChange = false;
		void ChangeTurn();
	public:
		TurnOrder(std::vector<Character> &characters);
		void Update();
		void Destroy();
		void ActivateTurnChange() {turnChange = true;};
};

#endif
