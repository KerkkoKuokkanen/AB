
#ifndef AXE_JUMP_ANIM_H
# define AXE_JUMP_ANIM_H

# include "../../ab.h"

typedef struct s_SpeedSprite
{
	Sprite *sprite;
	int counter;
}				t_SpeedSprite;

class AxeJumpAnim
{
	private:
		std::vector<t_SpeedSprite> speedSprites;
		Sprite *attackTrail = NULL;
		Character *character;
		Character *target;
		SDL_Point pos;
		int counter = 0;
		int secondPhaseCounter = 0;
		int speedSpriteCounter = 0;
		bool secondPhase = false;
		SDL_Point ogPos = {0, 0};
		void StartJump();
		void UpdateJump();
		void CreateSpeedSprite();
		void UpdateSpeedSprite();
		void StartSecondPhase();
		void UpdateSecondPhase();
		void CreateLandingDusts();
	public:
		bool done = false;
		bool createDamage = false;
		ThrowArch *arch = NULL;
		AxeJumpAnim(Character *character, Character *target, SDL_Point pos);
		~AxeJumpAnim() {Destroy();};
		void Update();
		void Destroy();
};

#endif
