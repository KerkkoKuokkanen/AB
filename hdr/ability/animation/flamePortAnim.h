
#ifndef FLAME_PORT_ANIM
# define FLAME_PORT_ANIM

# include "../../ab.h"

# define FLAME_PORT_PART_DISTANCE 50
# define FLAME_PORT_COLOR_CHANGE_TIME 40
# define FLAME_PORT_PART_START_SPEED 200.0f
# define FLAME_PORT_SECOND_PHASE_TIME 75

typedef struct s_FlamePortPart
{
	SDL_FPoint target;
	SDL_FPoint direction;
	float speed;
	float phaseDist;
	bool atTarget;
	Sprite *sprite;
}				t_FlamePortPart;

class FlamePort : public AbBase
{
	private:
		Character *character;
		SDL_Point target;
		SDL_Point ogPosition = {0, 0};
		std::vector<t_FlamePortPart> particles;
		void ChangeColor();
		void CreateParticles(int y, int yTarg);
		void UpdateParticles();
		void JustMoveParticles(t_FlamePortPart &part);
		void MoveToTarget(t_FlamePortPart &part);
		void CreateSecondPhase();
		void UpdateLastPhase();
		void StartLastPhase();
		int alpha = 0;
		int counter = 0;
		bool partSecondPhase = false;
		float distance;
		bool lastPhase = false;
		bool lastPhaseStarted = false;
	public:
		bool done = false;
		bool createSelfDamage = false;
		FlamePort(Character *character, SDL_Point target);
		~FlamePort() {Destroy();};
		void Update();
		void Destroy();
};

#endif
