
#ifndef PHANTOM_KNIGHT_H
# define PHANTOM_KNIGHT_H

# include "../../ab.h"

class PhantomKnight
{
	private:
		Character *character = NULL;
		Sprite *knight;
		Sprite *stand;
		SDL_Point position = {0, 0};
		int hp = 0;
		int turns = 0;
		int currText = 0;
		int currentTurn = 0;
		void UpdateSprites();
		void CheckTurns();
		bool cTurn = true;
	public:
		bool done = false;
		PhantomKnight(Character *character, t_Ability *ability, SDL_Point pos);
		~PhantomKnight() {Destroy();};
		void Update();
		void Destroy();
};

#endif
