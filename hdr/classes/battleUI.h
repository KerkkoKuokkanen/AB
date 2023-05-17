
#ifndef BATTLE_UI_H
# define BATTLE_UI_H

# include "../ab.h"

class CharacterUI
{
	private:
		std::vector<Character*> characters;
		Bar *health;
		Bar *armor;
	public:
		bool active = false;
		CharacterUI();
		void Update();
		void Destroy();
};

#endif
