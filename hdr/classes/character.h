
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
	public:
		Sprite *sprite;
		Character(bool allied = true);
		void AddToRender();
		void Update();
		void DeleteCharacter();
		int getWidth() {return (width);};
		int getHeight() {return (height);};
};

#endif
