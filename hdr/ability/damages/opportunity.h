
#ifndef OPPORTUNITY_H
# define OPPORTUNITY_H

# include "../../ab.h"

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
		Vector GetDirection();
		void StartDamage();
		void CreateDamageOrMiss();
	public:
		void Update();
		void Destroy();
};

#endif
