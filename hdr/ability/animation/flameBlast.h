
#ifndef FLAME_BLAST_H
# define FLAME_BLAST_H

# include "../../ab.h"

typedef struct s_FireBall
{
	FireBall *fireBall;
	SDL_Point target;
	bool atGoal;
	bool done;
	bool missing;
}				t_FireBall;

class FlameBlast : public AbBase
{
	private:
		std::vector<SDL_Point> targets;
		std::vector<t_FireBall> fireBalls;
		std::vector<t_HitReturn> retPoints;
		Sprite *aura = NULL;
		Character *character;
		t_Ability *ability;
		CharacterMover *mover = NULL;
		void UpdateAura();
		void CreateFireBall();
		bool CheckIfDone();
		void UpdateFireBalls();
		Vector getDirection(bool bigDir);
		void IncrementIterator();
		void CreateParticles();
		Color getColor();
		int GetPartAmount();
		void UpdateMover();
		int counter = 0;
		int amount;
		int alpha = 0;
		int iterator = 0;
	public:
		bool destroy = false;
		FlameBlast(Character *character, std::vector<SDL_Point> &targets, t_Ability *ability);
		~FlameBlast() {Destroy();};
		std::vector<t_HitReturn> &GetTargets();
		void Update();
		void Destroy();
};

#endif
