
#ifndef TELEPORT_ABILITY_H
# define TELEPORT_ABILITY_H

# include "../../ab.h"

typedef struct s_PartSavePosition
{
	SDL_Point place;
	int alpha;
}				t_PartSavePostion;

typedef struct s_TeleParticle
{
	Sprite *particle;
	SDL_FPoint direction;
	float speed;
	int life;
	float drag;
	float yAdd;
	std::vector<t_PartSavePostion> saves;
}				t_TeleParticle;

class TelePort : public AbBase
{
	private:
		std::vector<t_TeleParticle> particles = {};
		SDL_Point startPosition = {0, 0};
		SDL_Point targetPosition = {0, 0};
		SDL_Point targetDest = {0, 0};
		Character *character = NULL;
		SDL_Surface *sur = NULL;
		void ManageCreatingParticles();
		void CreateParticles(int start, int end);
		void ActivateParticles();
		int ManageParticleLifeAndAlpha(int index);
		SDL_Point GetCurrentPlace(int index);
		void ManageParticleMoving();
		void ManageFirstPhaseParts();
		void ManageSecondPhase();
		void MoveSecondPhaseParts();
		int counter = 0;
		int partCounter = 0;
		bool firstPhaseDone = false;
		bool secondPhaseDone = false;
		int countSave = 0;
	public:
		bool done = false;
		bool createMove = false;
		TelePort(Character *moved, SDL_Point goal);
		~TelePort() {Destroy();};
		void Update();
		void Destroy();
};

#endif
