
#ifndef CONTROL_H
# define CONTROL_H

# include "../ab.h"

class Control
{
	private:
		SDL_Point pos;
		Sprite *sprite = NULL;
	public:
		Control(SDL_Point pos, bool ally);
		~Control() {Destroy();};
		void Update();
		void Destroy();
};

#endif
