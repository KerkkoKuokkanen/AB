
#ifndef OBJECT_H
# define OBJECT_H

# include "../ab.h"

namespace ObjectSigns
{
	enum
	{
		BUSH,
		DEAD_TREE,
		SMALL_TREE,
		STUMP,
		TREE
	};
};

class Object
{
	private:
		SDL_Point pos;
		SDL_Surface *sur;
		SDL_Rect getRect(int type, SDL_Point position);
		int getObjSize(int type);
		t_TextAndSur getTextureAndSurface(int type);
		void CheckMouseHover();
		bool fadeOnMouseOver;
		int overCounter;
		int GetTheHeight();
	public:
		int size;
		Sprite *sprite;
		Object(int type, SDL_Point position, bool fadeOnMouseOver = true);
		void Update();
};

#endif
