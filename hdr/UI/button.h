
#ifndef BUTTON_H
# define BUTTON_H

# include "../ab.h"

# define BUTTON_HOVER 1
# define BUTTON_PRESS 2
# define NO_CONTACT 0

class Button
{
	private:
		Sprite *sprite;
		SDL_Rect clickBox;
		bool active = true;
	public:
		Button(SDL_Texture *button, SDL_Rect dest, SDL_Rect clickBox);
		void SetTexture(SDL_Texture *texture) {sprite->setTexture(texture);};
		void SetDest(SDL_Rect dest) {sprite->dest = dest;};
		void Position(Vector place) {sprite->Position(place);};
		void SetClickBox(SDL_Rect clickBox);
		void Destroy() {sprite->Destroy();};
		void Deactivate() {sprite->Deactivate(); active = false;};
		void Activate() {sprite->Activate(); active = true;};
		void ClearColor() {sprite->ClearColorMod();};
		int Update();
};

#endif
