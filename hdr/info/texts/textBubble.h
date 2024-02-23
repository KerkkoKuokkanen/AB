
#ifndef TEXT_BUBBLE_H
# define TEXT_BUBBLE_H

# include "../../ab.h"

typedef struct s_SnippetPos
{
	Snippet *snippet;
	SDL_Point pos;
}				t_SnippetPos;

typedef struct s_SpritePos
{
	Sprite *sprite;
	SDL_Point pos;
}				t_SpritePos;

class TextBubble
{
	private:
		Sprite *outline = NULL;
		std::vector<t_SnippetPos> snippets = {};
		std::vector<t_SpritePos> sprites = {};
		SDL_Point pos = {0, 0};
		bool followMouse = false;
		SDL_Point followPos = {0, 0};
		int follorCorner = 0;
		int GetFollowX();
		int GetFollorY();
	public:
		int id = 0;
		TextBubble(SDL_Point position);
		~TextBubble() {Destroy();};
		void SetFollowCorner(int cornerSign);
		void SetMouseFollow(SDL_Point followPos);
		void SetPosition(SDL_Point position);
		void AddSnippetToBubble(Snippet *snippet, SDL_Point pos);
		void AddSpriteToBubble(Sprite *sprite, SDL_Point pos);
		void SetUpOutline(int xAdd, int yAdd);
		void Update();
		void Destroy();
};

#endif
