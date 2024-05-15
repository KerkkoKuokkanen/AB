
#ifndef ACID_RAIN_ANIM
# define ACID_RAIN_ANIM

# include "../../ab.h"

typedef struct s_RainDrop
{
	Sprite *drop;
	int heightDestination;
	SDL_FPoint direction;
	int alpha;
	float speed;
}				t_RainDrop;

class AcidRain : public AbBase
{
	private:
		WitchAnimation *animation = NULL;
		std::vector<t_RainDrop> drops = {};
		int counter = 0;
		void UpdateAnimation();
		void UpdateDrops();
		void CreateDrops();
		SDL_Point GetDropPosition();
		SDL_Point GetLandingPosition();
		int GetOrderLayer(int landY);
		Vector GetDirection(SDL_Point start, SDL_Point land);
		void MoveDrop(t_RainDrop *drop);
		void ManageDropAlpha(t_RainDrop *drop);
		void CreateDropParticle(t_RainDrop *drop);
		void PlayRainSound();
		SDL_Point defDropPos = {0, 0};
		SDL_Point tileDestMid = {0, 0};
		SDL_Point targetDestination = {0, 0};
		float spriteDepth = 0.0f;
		int intensity = 0;
	public:
		bool done = false;
		bool createDamage = false;
		AcidRain(Character *character, SDL_Point destination, int intensity);
		~AcidRain() {Destroy();};
		void Update();
		void Destroy();
};

#endif
