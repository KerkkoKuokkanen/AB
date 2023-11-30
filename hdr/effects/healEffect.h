
#ifndef HEAL_EFFECT_H
# define HEAL_EFFECT_H

# include "../ab.h"

class HealEffect
{
	private:
		Character *character;
		Character *source;
		int counter = 0;
		int amount = 0;
		void UpdateColor();
		void CreateTextSnippet();
	public:
		bool done = false;
		HealEffect(Character *character, Character *source, int amount);
		~HealEffect() {Destroy();};
		void Update();
		void Destroy();
};

#endif
