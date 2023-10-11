
#ifndef ABILITY_OPPORTUNITY_H
# define ABILITY_OPPORTUNITY_H

# include "../../ab.h"

class AbilityOpportunity
{
	private:
		bool triedForAxe = false;
		bool hits = false;
		CharacterMover *mover = NULL;
		Character *target = NULL;
		Character *GetTarget();
		Character *GetDamager(Character *target);
		Character *CheckValid(SDL_Point pos);
		void AxeSlashUpdate();
		void CreateDamageOrMiss();
		void ManageAbilityType();
		void StartDamage(Character *damager);
	public:
		~AbilityOpportunity() {Destroy();};
		void Update();
		void Destroy();
};

#endif
