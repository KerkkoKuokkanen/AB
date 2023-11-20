
#ifndef OPPORTUNITY_H
# define OPPORTUNITY_H

# include "../../ab.h"

typedef struct s_RandChar
{
	t_Damager used;
	int value;
}				t_RandChar;

class OpportunityAttack
{
	private:
		t_Damager damager = {NULL, 0};
		Character *target = NULL;
		SpriteMover *mover = NULL;
		Character *AnyOneMoving();
		int tried = false;
		bool hits = false;
		void CheckForTargets();
		t_Damager GetDamager();
		bool CheckValid(SDL_Point pos);
		bool CheckValidForAdditional(SDL_Point pos);
		Vector GetDirection();
		void StartDamage();
		void CreateDamageOrMiss();
		void AddAdditionalDamagers(SDL_Point pos, std::vector<t_RandChar> &adds);
	public:
		void Update();
		void Destroy();
};

#endif
