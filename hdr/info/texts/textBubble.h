
#ifndef TEXT_BUBBLE_H
# define TEXT_BUBBLE_H

# include "../../ab.h"

class TextBubble
{
	private:
		Sprite *outlines[2] = {NULL, NULL};
		std::vector<Snippet*> snippets = {};
	public:
		TextBubble(SDL_Point position);
		~TextBubble() {Destroy();};
		void AddTextToBubble(const char *text, int size, Color color);
		void AddSnippetToBubble(Snippet *snippet);
		void Update();
		void Destroy();
};

#endif
