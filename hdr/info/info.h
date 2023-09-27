
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
		std::vector<SupplyEffect*> supplyEffects;
		std::vector<BuffEffect*> buffEffects;
		std::vector<HostEffect*> hostEffects;
		void UpdateSnippets();
		void FindHoveredCharacter();
		bool KilledOrDamaged();
		void UpdateBar();
		void UpdateSupplyEffects();
		void UpdateBuffEffects();
		void UpdateHostEffects();
	public:
		bool overInfo = false;
		Info();
		~Info() {Destroy();};
		void AddSnippet(FlyingSnippet *snippet);
		void AddSupplyEffect(SupplyEffect *add) {supplyEffects.push_back(add);};
		void AddBuffEffect(BuffEffect *add) {buffEffects.push_back(add);};
		void AddHostEffect(HostEffect *add) {hostEffects.push_back(add);};
		void Update();
		void Destroy();
};

#endif
