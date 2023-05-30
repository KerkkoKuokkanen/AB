
#ifndef PARTICLE_MANAGER_H
# define PARTICLE_MANAGER_H

# include "../ab.h"

# define PART_LIFE 120

typedef struct s_Particle
{
	Particle *part;
	int lifeTime, total;
	Uint8 r, g, b;
	Uint8 sr, sg, sb;
	float yAdd;
	float speed;
	SDL_FPoint dir;
}				t_Particle;

class ParticleManager
{
	private:
		std::vector<Particle*> particles;
		std::vector<t_Particle> modParts;
		void ManageColorChange(Particle *part);
		void ManageAlphaChange(Particle *part);
		void ManageModColor(t_Particle *part);
		void ManageModAlpha(t_Particle *part);
		void ManageYAdd(t_Particle *part);
	public:
		void Update();
		void CreateParticle(Vector dir, Vector place, float speed);
		void CreateModParticle(Vector dir, Vector place, float speed, Color start, Color end, int life, float drag, float yAdd = 0.0f);
};

#endif
