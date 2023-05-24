
#ifndef PARTICLE_MANAGER_H
# define PARTICLE_MANAGER_H

# include "../ab.h"

# define PART_LIFE 120

class ParticleManager
{
	private:
		std::vector<Particle*> particles;
		void ManageColorChange(Particle *part);
		void ManageAlphaChange(Particle *part);
	public:
		void Update();
		void CreateParticle(Vector dir, Vector place, float speed);
};

#endif
