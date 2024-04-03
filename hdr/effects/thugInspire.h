
#ifndef THUG_INSIPRE_EFFECT_H
# define THUG_INSIPRE_EFFECT_H

# include "../ab.h"

class ThugInspire
{
	private:
		Character *target;
		void ManageAlpha();
		int counter = 0;
	public:
		bool done = false;
		ThugInspire(Character *target);
		~ThugInspire() {Destroy();};
		void Update();
		void Destroy();
};

#endif
