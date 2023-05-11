#ifndef TURN_INDICATOR_H
# define TURN_INDICATOR_H

# include "../ab.h"

class TurnIndicator
{
	private:
		Character *chosen = NULL;
	public:
		TurnIndicator();
		void Update();
		SDL_Point FindCharacter(Character *character);
		void SetCharacter(Character *character);
		void Deactivate() {chosen = NULL;};
		Character *getChosen() {return (chosen);};
};

#endif
