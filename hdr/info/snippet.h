
#ifndef SNIPPET_H
# define SNIPPET_H

# include "../ab.h"

class Snippet
{
	private:
		int amount = 100;
		bool outlineBool = false;
		SDL_Texture *text = NULL;
		Sprite *sprite = NULL;
		Sprite *outline[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
		void CreateOutline(SDL_Rect dest, int layer, bool staticSprite);
		std::string string;
	public:
		Snippet(const char *text, int fontType, bool outline, SDL_Point pos, int size, int offset, int layer, bool staticSprite);
		void SetOrderLayer(int order);
		void SetOutlineAmount(int amount);
		void Position(SDL_Point pos);
		void Move(Vector amount);
		void SetAlphaMod(Uint8 alpha);
		void ClearAlphaMod();
		void SetScaled(bool scaled);
		void SetDepth(float z);
		const char *GetText() {return (string.c_str());};
		void SetColor(Uint8 r, Uint8 g, Uint8 b);
		void SetOutlineColor(Uint8 r, Uint8 g, Uint8 b);
		~Snippet() {Destroy();};
		void Destroy();
};

#endif
