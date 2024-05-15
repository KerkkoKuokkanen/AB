
#ifndef INFO_H
# define INFO_H

# include "../ab.h"

typedef struct s_CritFilter
{
	int time;
	Sprite *sprite;
}				t_CritFilter;

class Info
{
	private:
		int barh = 0, bara = 0;
		bool infoBarBara = false;
		Character *hovered = NULL;
		Counter *counter = NULL;
		ControlSetter *controls = NULL;
		t_CritFilter critFilter = {0, NULL};
		StunUpdates *stunUpdates = NULL;
		MovementEnergy *movementEnergy = NULL;
		InfoBar *bar = NULL;
		ColorEffects *colorEffects = NULL;
		HealthColoring *healthColoring = NULL;
		IconBarHandler *iconHandler = NULL;
		StatusInfo *statusInfo = NULL;
		HitChanceBubble *hitChanceBubble = NULL;
		FrenzyColorer *frenzyColorer = NULL;
		std::vector<FlyingSnippet*> snippets;
		std::vector<SupplyEffect*> supplyEffects;
		std::vector<BuffEffect*> buffEffects;
		std::vector<HostEffect*> hostEffects;
		std::vector<NailBombBlast*> nailBombs;
		std::vector<AcidBombBlast*> acidBombs;
		std::vector<SlowedEffect*> slowEffects;
		std::vector<HealEffect*> healEffects;
		std::vector<ShieldBashEffect*> shieldBashEffects;
		std::vector<ThugInspire*> inspireEffecst;
		void UpdateSnippets();
		void FindHoveredCharacter();
		bool KilledOrDamaged();
		void UpdateBar();
		void UpdateSupplyEffects();
		void UpdateBuffEffects();
		void UpdateHostEffects();
		void UpdateBombEffects();
		void UpdateSlowEffects();
		void UpdateCritFilter();
		void UpdateStatusInfo();
		void UpdateFrenzy();
		int hoverIcon = -1;
	public:
		bool overInfo = false;
		bool overInfoBar = false;
		Info();
		~Info() {Destroy();};
		void InitInfo();
		void AddSnippet(FlyingSnippet *snippet);
		void AddSupplyEffect(SupplyEffect *add) {supplyEffects.push_back(add);};
		void AddBuffEffect(BuffEffect *add) {buffEffects.push_back(add);};
		void AddHostEffect(HostEffect *add) {hostEffects.push_back(add);};
		void AddHealEffect(HealEffect *add) {healEffects.push_back(add);};
		void AddSlowEffect(SlowedEffect *add) {slowEffects.push_back(add);};
		void AddShieldBashEffect(ShieldBashEffect *add) {shieldBashEffects.push_back(add);};
		void AddInspireEffect(ThugInspire *add) {inspireEffecst.push_back(add);};
		void AddToFrenzyColorer(Character *target) {frenzyColorer->AddCharacter(target);};
		void AddBombEffect(void *effect, int abilityType);
		void SetCritFilter();
		void AddColorEffect(Sprite *sprite, int time, Color color, int delay) {colorEffects->AddEffect(sprite, time, color, delay);};
		void InfoBarTargetValues(int health, int armor) {barh = health; bara = armor; infoBarBara = true; if (bar != NULL) {delete bar; bar = NULL;}};
		void InfoBarDeactivate(bool button) {infoBarBara = button;};
		void Update();
		void Destroy();
};

#endif
