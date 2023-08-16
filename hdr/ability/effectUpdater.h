
#ifndef EFFECT_UPDATER_H
# define EFFECT_UPDATER_H

# include "../ab.h"

typedef struct s_AbilityEffect
{
	SDL_Point pos;
	t_Ability *ability;
	void *effect;
}				t_AbilityEffect;

class EffectUpdater
{
	private:
		int turnChecker = 0;
		void CreateEffect(Character *character, t_AbilityEffect &add);
		void DeleteEffect(t_AbilityEffect &effect);
		void UpdateEffect(t_AbilityEffect &effect, int index);
		t_AbilityEffect *CheckForEffectAlready(int type, SDL_Point pos);
	public:
		std::vector<t_AbilityEffect> effects;
		void SetEffect(Character *character, SDL_Point pos, t_Ability *ability);
		void Update();
		void Clear();
};

#endif
