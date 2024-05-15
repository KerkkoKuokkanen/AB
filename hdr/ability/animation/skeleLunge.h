
#ifndef SKELE_LUNGE_H
# define SKELE_LUNGE_H

# include "../../ab.h"

typedef struct s_TrailSprite
{
	Sprite *sprite;
	int counter;
}				t_TrailSprite;

class SkeleLunge : public AbBase
{
	private:
		std::vector<t_TrailSprite> spriteTrail;
		Character *skele = NULL;
		Character *target = NULL;
		ThrowArch *lungeArch = NULL;
		SDL_Point pos = {0, 0};
		SDL_Point startPosition = {0, 0};
		bool firstPhase = true;
		int counter = 0;
		int speedSpriteCounter = 0;
		void CreateTrailSprites();
	public:
		bool done = false;
		bool createDamage = false;
		SkeleLunge(Character *skele, Character *target, SDL_Point pos);
		~SkeleLunge() {Destroy();};
		void Update();
		void Destroy();
};

#endif
