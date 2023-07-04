
#ifndef EFFECT_UPDATER_H
# define EFFECT_UPDATER_H

# include "../ab.h"

typedef struct s_AbilityEffect
{
	int duration;
	int time;
	SDL_Point pos;
	t_Ability ability;
	void *effect;
}				t_AbilityEffect;

class EffectUpdater
{
	private:
		int turnChecker = 0;
		std::vector<t_AbilityEffect> effects;
		void CreateEffect(t_AbilityEffect &add);
		void UpdateEffect(t_AbilityEffect &effect);
		void CheckTurnCounter();
		void DeleteEffect(void *effect, int type);
		t_AbilityEffect *CheckForEffectAlready(int type, SDL_Point pos);
	public:
		void SetEffect(int duration, SDL_Point pos, t_Ability ability);
		void Update();
		void Clear();
};

#endif
