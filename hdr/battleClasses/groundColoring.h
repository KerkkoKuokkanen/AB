
#ifndef GROUND_COLORING_H
# define GROUND_COLORING_H

# include "../ab.h"

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
