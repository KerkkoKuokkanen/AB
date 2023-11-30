
#ifndef HEALTH_TRANSFER_H
# define HEALTH_TRANSFER_H

# include "../../ab.h"

typedef struct s_HealthParticle
{
	Sprite *sprite;
	SDL_FPoint direction;
	float speed;
	float dirChangeStrength;
	int time;
}				t_HealthParticle;

class HealthTransfer
{
	private:
		std::vector<t_HealthParticle> particles = {};
		Character *start;
		Character *end;
		SDL_Surface *sur;
		SDL_Point goal = {0, 0};
		void ManageParticles();
		void ManageCreatingParticles();
		void ManageParticleMoving();
		Vector GetGoalDirection(int index);
		void CreateParticles(int start, int end);
		bool CheckIfAtGoal(int index);
		int totalAmount = 0;
		int counter = 0;
		int partCounter = 0;
	public:
		int damageDoneSave = 0;
		bool done = false;
		bool createDamage = false;
		bool createEffect = false;
		HealthTransfer(Character *start, Character *end);
		~HealthTransfer() {Destroy();};
		void Update();
		void Destroy();
};

#endif
