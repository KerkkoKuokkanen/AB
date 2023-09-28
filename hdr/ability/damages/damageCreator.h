
#ifndef DAMAGE_CREATOR_H
# define DAMAGE_CREATOR_H

# include "../../ab.h"

typedef struct s_Sound
{
	Mix_Chunk *sound;
	int channel;
	int loops;
}				t_Sound;

typedef struct s_Damage
{
	Character *character;
	int armorDamage;
	int healthDamage;
	Vector partDir;
	int time;
	SDL_Rect ogPos;
	Uint8 r, g, b;
	bool partDone;
	bool move;
}				t_Damage;

class DamageCreator
{
	private:
		std::vector<t_Damage> damages;
		std::vector<Particle*> particles;
		void ColorManage(Character *character, int time);
		void MoveManage(Character *character, int time, Vector direction, SDL_Rect dest);
		void CreateParticles(Character *character, Vector partDir, Color start);
		float GetSpeed(Vector dir, Vector genDir);
		int GetLifeTime();
		float GetDrag();
		float GetYAdd();
	public:
		void CreateDamage(Character *character, Color startColor, int armorDamage, int healthDamage, Vector partDir, std::vector<t_Sound> &sounds, bool move = true);
		void Update();
};

#endif
