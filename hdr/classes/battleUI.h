
#ifndef BATTLE_UI_H
# define BATTLE_UI_H

# include "../ab.h"

class CharacterUI
{
	private:
		std::vector<Character*> characters;
	public:
		bool active = false;
		CharacterUI();
		void Update();
};

#endif
