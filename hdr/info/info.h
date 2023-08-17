
#ifndef INFO_H
# define INFO_H

# include "../ab.h"

class Info
{
	private:
		Character *hovered;
		HoverBars *hoverBars;
		Counter *counter;
		ControlSetter *controls;
		FilterModeBars *filterMode = NULL;
		StunUpdates *stunUpdates = NULL;
		MovementEnergy *movementEnergy = NULL;
		void FindHoveredCharacter();
		void ManageFilterMode();
		bool KilledOrDamaged();
	public:
		bool overInfo = false;
		Info();
		~Info() {Destroy();};
		void Update();
		void Destroy();
};

#endif
