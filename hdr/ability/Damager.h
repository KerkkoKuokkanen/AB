
#ifndef DAMAGER_H
# define DAMAGER_H

# include "../ab.h"

class Damager
{
	private:
		DamageCreator damageCreator;
		std::vector<Character*> targets;
		Vector GetDirection(Character *character, Character *target);
	public:
		void AddDamage(t_Ability *ability, Character *character, std::vector<SDL_Point> &targets);
		void Update();
};

#endif
