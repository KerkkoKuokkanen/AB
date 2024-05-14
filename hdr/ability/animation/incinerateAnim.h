
#ifndef INCINERATE_ANIM_H
# define INCINERATE_ANIM_H

# include "../../ab.h"

typedef struct s_IncinerateStruct
{
	SDL_Point pos;
	Sprite *ball;
	Sprite *aura;
}				t_IncinerateStruct;

class Incinerate : AbBase
{
	private:
		Character *character = NULL;
		Sprite *handBall = NULL;
		Sprite *handParts = NULL;
		std::vector<t_IncinerateStruct> balls = {};
		std::vector<Sprite*> explosions = {};
		void CreateSprite(t_IncinerateStruct &ball, Character *target);
		void CreateHandBall();
		void UpdateHandBall();
		void UpdateBalls();
		void HandleSpriteAlpha(Sprite *sprite);
		void MoveHandBall();
		void MoveABall(Sprite *sprite);
		void HandleAuraAlpha(Sprite *sprite);
		void RotateSprite(Sprite *sprite);
		void StartSecondPhase();
		void CreateExplosions();
		void CreateParticles(SDL_Rect dest);
		void CreateHandParticles();
		void UpdateExplosions();
		void UpdateHandParts();
		void RemoveExplosions();
		void ExplosionAngle();
		void CreateBallParticles(Sprite *ball);
		int counter = 0;
		int alphaMod = 21;
		int alphaCount = 0;
		bool everyOther = false;
		bool secondPhase = false;
		int ballPartAmount = 2;
	public:
		bool done = false;
		bool createDamage = false;
		Incinerate(Character *character, std::vector<SDL_Point> &targets);
		~Incinerate() {Destroy();};
		void Update();
		void Destroy();
};

#endif
