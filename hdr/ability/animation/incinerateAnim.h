
#ifndef INCINERATE_ANIM_H
# define INCINERATE_ANIM_H

# include "../../ab.h"

typedef struct s_IncinerateStruct
{
	SDL_Point pos;
	Sprite *ball;
	Sprite *aura;
}				t_IncinerateStruct;

class Incinerate
{
	private:
		Character *character = NULL;
		Sprite *handBall = NULL;
		std::vector<t_IncinerateStruct> balls;
		void CreateSprite(t_IncinerateStruct &ball, Character *target);
		void CreateHandBall();
		void UpdateHandBall();
		void UpdateBalls();
		int counter = 0;
	public:
		bool done = false;
		Incinerate(Character *character, std::vector<SDL_Point> &targets);
		~Incinerate() {Destroy();};
		void Update();
		void Destroy();
};

#endif
