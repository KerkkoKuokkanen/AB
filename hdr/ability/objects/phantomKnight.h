
#ifndef PHANTOM_KNIGHT_H
# define PHANTOM_KNIGHT_H

# include "../../ab.h"

class PhantomKnight
{
	private:
		Sprite *knight;
		Sprite *stand;
		int hp = 0;
		int turns = 0;
		int currText = 0;
		int currentTurn = 0;
		void UpdateSprites();
		void CheckTurns();
		void CreateParticles();
		bool cTurn = true;
	public:
		SDL_Point position = {0, 0};
		Character *character = NULL;
		bool done = false;
		PhantomKnight(Character *character, t_Ability *ability, SDL_Point pos);
		~PhantomKnight() {Destroy();};
		void Update();
		void Destroy();
};

#endif