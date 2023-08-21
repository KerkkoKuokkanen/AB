
#ifndef INFO_BARS_H
# define INFO_BARS_H

# include "../ab.h"

class InfoBar
{
	private:
		SDL_Texture *charText = NULL;
		Sprite *text[5] = {NULL, NULL, NULL, NULL, NULL};
		Sprite *outline = NULL;
		Bar *health = NULL;
		Bar *armor = NULL;
		Bar *fatigue = NULL;
		void CreateText();
		void CreateBars();
		SDL_Rect GetTextDest(std::string &str);
	public:
		Character *character = NULL;
		InfoBar(Character *character);
		~InfoBar() {Destroy();};
		void Update();
		void Destroy();
};

#endif
