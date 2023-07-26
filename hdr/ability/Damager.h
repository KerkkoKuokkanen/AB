
#ifndef DAMAGER_H
# define DAMAGER_H

# include "../ab.h"

typedef struct s_Bars
{
	Bar *health;
	Bar *armor;
	Character *target;
	int timer;
}				t_Bars;

class Damager
{
	private:
		DamageCreator damageCreator;
		std::vector<Character*> targets;
		std::vector<t_Bars> bars;
		Vector GetDirection(Character *character, Character *target);
		void PositionBars(Character *target, t_Bars &bars);
		void CreateBars(Character *target);
		void UpdateBars();
	public:
		void AddDamage(t_Ability *ability, Character *character, std::vector<SDL_Point> &targets);
		void Update();
};

#endif
