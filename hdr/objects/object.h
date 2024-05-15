
#ifndef OBJECT_H
# define OBJECT_H

# include "../ab.h"

namespace ObjectSigns
{
	enum
	{
		BUSH,
		DEAD_TREE,
		STUMP,
		TREE
	};
};

class Object
{
	private:
		SDL_Point pos;
		SDL_Surface *surLeft;
		SDL_Surface *surRight;
		SDL_Rect getRect(int type, SDL_Point position);
		int getObjSize(int type);
		int getTextureAndSurface(int type);
		void CheckMouseHover();
		bool fadeOnMouseOver;
		int overCounter;
		int GetTheHeightLeft();
		int GetTheHeightRight();
	public:
		int size;
		Sprite *spriteLeft = NULL;
		Sprite *spriteRight = NULL;
		Object(int type, SDL_Point position, bool fadeOnMouseOver = true);
		~Object() {Destroy();};
		void Update();
		void Destroy();
};

#endif
