
#ifndef OW_PLAYER_H
# define OW_PLAYER_H

# include "tools/mapObj.h"
# include "../render/sprite.h"
# include "tools/owSpriteMover.h"

class Player : public MapObj
{
	private:
		Sprite *sprite = NULL;
		OwSpriteMover *mover = NULL;
		int moveDelayer = 0;
		int delayTime = 12;
		void MovePlayer();
	public:
		Player(SDL_Point pos);
		~Player() {Destroy();};
		void Update();
		void Destroy();
};

#endif
