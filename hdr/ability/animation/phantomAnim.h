
#ifndef PHANTOM_ANIM_H
# define PHANTOM_ANIM_H

# include "../../ab.h"

typedef struct s_SpriteAndSRect
{
	Sprite *sprite;
	SDL_Rect srect;
}				t_SpriteAndSRect;

class PhantomAnim
{
	private:
		std::vector<t_SpriteAndSRect> sprites;
		int counter = 0;
		void CreateSprite(SDL_Point target);
		void CreateParticles(SDL_Point target);
		void UpdateKnight();
		void ScaleKnight(int index);
	public:
		bool done = false;
		PhantomAnim(std::vector<SDL_Point> targets);
		~PhantomAnim() {Destroy();};
		void Update();
		void Destroy();
};

#endif
