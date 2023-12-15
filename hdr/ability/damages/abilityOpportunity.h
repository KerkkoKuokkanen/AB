
#ifndef ABILITY_OPPORTUNITY_H
# define ABILITY_OPPORTUNITY_H

# include "../../ab.h"

class AbilityOpportunity
{
	private:
		bool triedForAxe = false;
		bool hits = false;
		SpriteMover *mover = NULL;
		Character *target = NULL;
		t_Damager damager = {NULL, 0};
		Character *GetTarget();
		t_Damager GetDamager(Character *target);
		bool CheckValid(SDL_Point pos);
		void AxeSlashUpdate();
		bool CheckValidForAdditional(SDL_Point pos);
		void AddAdditionalDamagers(SDL_Point pos, std::vector<t_RandChar> &adds);
		void CreateDamageOrMiss();
		void ManageAbilityType();
		void StartDamage();
	public:
		~AbilityOpportunity() {Destroy();};
		void Update();
		void Destroy();
};

#endif
