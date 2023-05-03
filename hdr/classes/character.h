
#ifndef CHARACTER_H
# define CHARACTER_H

# include "../ab.h"

class Character
{
	private:
		std::vector<SDL_Texture*> textures;
		int idleCounter = 0;
		int currentTexture = 0;
		int width, height;
		bool ally = true;
		SDL_Point coord = {0, 0};
		SDL_Rect clickBox = {0, 0, 0, 0};
	public:
		Sprite *sprite;
		Character(bool allied = true);
		void AddToRender();
		void Update();
		void DeleteCharacter();
		int getWidth() {return (width);};
		int getHeight() {return (height);};
		void setCoord(SDL_Point &coord);
		SDL_Point &getCoord();
		void Position(Vector to);
		void Move(Vector amount);
		bool hover = false;
		bool clicked = false;
		bool turn = true;
		bool moving = false;
		int moves = 10;
};

#endif
