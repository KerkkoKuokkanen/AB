
#ifndef DAMAGE_CREATOR_H
# define DAMAGE_CREATOR_H

# include "../ab.h"

typedef struct s_Damage
{
	Character *character;
	int armorDamage;
	int healthDamage;
	Vector partDir;
	int time;
	SDL_Rect ogPos;
}				t_Damage;

class DamageCreator
{
	private:
		std::vector<t_Damage> damages;
		std::vector<Particle*> particles;
		void ColorManage(Character *character, int time);
		void MoveManage(Character *character, int time, Vector direction, SDL_Rect dest);
	public:
		void CreateDamage(Character *character, int armorDamage, int healthDamage, Vector partDir);
		void Update();
};

#endif
