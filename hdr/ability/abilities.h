
#ifndef ABILITIES_H
# define ABILITIES_H

# include "../ab.h"

class Abilities
{
	private:
		t_Ability *ability = NULL;
		Character *character = NULL;
		Selector *selector = NULL;
		GroundColoring groundColoring;
		void SetSelector(t_Ability *ability, Character *character);
	public:
		bool active = false;
		void SetAbility(t_Ability *ability, Character *character);
		void SetMap() {groundColoring.SetMap();};
		void Upadte();
		void Clear();
};

#endif
