
#ifndef INFO_H
# define INFO_H

# include "../ab.h"

class Info
{
	private:
		Character *hovered;
		Counter *counter;
		ControlSetter *controls;
		StunUpdates *stunUpdates = NULL;
		MovementEnergy *movementEnergy = NULL;
		InfoBar *bar = NULL;
		void FindHoveredCharacter();
		bool KilledOrDamaged();
		void UpdateBar();
	public:
		bool overInfo = false;
		Info();
		~Info() {Destroy();};
		void Update();
		void Destroy();
};

#endif
