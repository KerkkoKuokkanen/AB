
#ifndef CHARACTER_H
# define CHARACTER_H

# include "../ab.h"

class Character
{
	private:
		Sprite *sprite;
		std::vector<SDL_Texture*> textures;
		int idleCounter = 0;
		int currentTexture = 0;
		int width, height;
	public:
		Character();
		void AddToRender();
		void Update();
		void DeleteCharacter();
};

#endif
