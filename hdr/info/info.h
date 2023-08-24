
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
		std::vector<FlyingSnippet*> snippets;
		void UpdateSnippets();
		void FindHoveredCharacter();
		bool KilledOrDamaged();
		void UpdateBar();
	public:
		bool overInfo = false;
		Info();
		~Info() {Destroy();};
		void AddSnippet(FlyingSnippet *snippet);
		void Update();
		void Destroy();
};

#endif
