
#ifndef OPPORTUNITY_H
# define OPPORTUNITY_H

# include "../../ab.h"

class OpportunityAttack
{
	private:
		Character *damager = NULL;
		Character *target = NULL;
		CharacterMover *mover = NULL;
		Character *AnyOneMoving();
		int tried = false;
		bool hits = false;
		void CheckForTargets();
		Character *GetDamager();
		Character *CheckValid(SDL_Point pos);
		Vector GetDirection();
		void StartDamage();
		void CreateDamageOrMiss();
	public:
		void Update();
		void Destroy();
};

#endif
