
#ifndef SHIELD_BASH_EFFECT_H
# define SHIELD_BASH_EFFECT_H

# include "../ab.h"

class ShieldBashEffect
{
	private:
		std::vector<t_Particle> particles = {};
		SDL_FPoint generalDirection = {0.0f, 0.0f};
		Character *target = NULL;
		SDL_Surface *targetSur = NULL;
		void CreateParticles(int start, int end);
		int count = 0;
		int partCount = 0;
	public:
		bool done = false;
		ShieldBashEffect(Character *caster, Character *target);
		~ShieldBashEffect() {Destroy();};
		void Update();
		void Destroy();
};

#endif
