
#ifndef ABILITY_MANAGER_H
# define ABILITY_MANAGER_H

# include "../ab.h"

class AbilityManager
{
	private:
		DaggerThrow *daggerThrow = NULL;
	public:
		bool abilityActive = false;
		void SetAbility(void *ability, int type);
		void ActivateAbility(t_Ability *ability);
		void Update();
		void ClearAbilities();
};

#endif
