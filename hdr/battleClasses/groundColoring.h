
#ifndef GROUND_COLORING_H
# define GROUND_COLORING_H

# include "../ab.h"

class Color
{
	public:
		Uint8 r, g, b;
		Color(Uint8 r, Uint8 g, Uint8 b) {Color::r = r; Color::g = g; Color::b = b;};
};

typedef struct s_CMap
{
	Sprite *sprite;
	Uint8 rh, gh, bh;
	Uint8 rl, gl, bl;
	bool colored;
}				t_CMap;

class GroundColoring
{
	private:
		bool fade = true;
		std::vector<std::vector<t_CMap>> spriteMap;
	public:
		bool active = false;
		void Update();
		void SetColoredPosition(SDL_Point pos, Color &high, Color &low);
		void SetColoredPosition(SDL_Point pos, Color &color);
		void SetColoredPositions(std::vector<SDL_Point> &positions, Color &high, Color &low);
		void SetColoredPositions(std::vector<SDL_Point> &positions, Color &color);
		void SetFade(bool fade) {GroundColoring::fade = fade;};
		void ClearPosition(SDL_Point pos);
		void ClearMap();
		void SetMap();
};

#endif
