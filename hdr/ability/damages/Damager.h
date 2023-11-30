
#ifndef DAMAGER_H
# define DAMAGER_H

# include "../../ab.h"

typedef struct s_Bars
{
	Bar *health;
	Bar *armor;
	Statuses *statusBar;
	Character *target;
	int timer;
}				t_Bars;

class Damager
{
	private:
		std::vector<Character*> targets;
		std::vector<t_Bars> bars;
		std::vector<AddStatus*> statuses = {};
	public:
		DamageCreator damageCreator;
		Vector GetDirection(SDL_Point character, Character *target);
		void AddDamage(t_Ability *ability, Character *character, std::vector<SDL_Point> &targets, bool sound = true);
		void AddOpportunityDamage(SDL_Point damager, Character *target);
		void AddPoisonDamage(Character *target, int amount);
		void AddBleedDamage(Character *target, int amount);
		void RemoveDamageFromCreator(Character *character) {damageCreator.RemoveCharacter(character);};
		void Update();
};

#endif
