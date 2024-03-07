
#ifndef MENU_H
# define MENU_H

# include "../../ab.h"

class Menu
{
	private:
		Sprite *backGround = NULL;
		int onScreen = 0;
		void CheckOnScreen();
		void PutMenuOnScreen();
		void ClearMenu();
	public:
		~Menu() {Destroy();};
		void Update();
		void Destroy();
};

#endif
