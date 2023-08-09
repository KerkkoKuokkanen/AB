
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
		DamageCreator damageCreator;
		std::vector<Character*> targets;
		std::vector<t_Bars> bars;
		std::vector<AddStatus*> statuses = {};
		Vector GetDirection(Character *character, Character *target);
		void PositionBars(Character *target, t_Bars &bars);
		void CreateBars(Character *target);
		void UpdateBars();
		void UpdateStatuses();
		void CreateDebuff(t_Ability *ability, Character *character, SDL_Point targ);
	public:
		void AddDamage(t_Ability *ability, Character *character, std::vector<SDL_Point> &targets, bool sound = true);
		void Update();
};

#endif
