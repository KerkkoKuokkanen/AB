
#include "../../hdr/global.h"

t_AbilityEffect *EffectUpdater::CheckForEffectAlready(int type, SDL_Point pos)
{
	for (int i = 0; i < effects.size(); i++)
	{
		if (effects[i].ability.type == type && effects[i].pos.x == pos.x && effects[i].pos.y == pos.y)
			return (&effects[i]);
	}
	return (NULL);
}

void EffectUpdater::CreateEffect(t_AbilityEffect &add)
{
	switch (add.ability.type)
	{
		case SMOKE_BOMB:
			add.effect = new SmokeEffect(add.pos);
			break ;
	}
}

void EffectUpdater::SetEffect(int duration, SDL_Point pos, t_Ability ability)
{
	t_AbilityEffect *check = CheckForEffectAlready(ability.type, pos);
	if (check != NULL)
	{
		check->duration = duration;
		check->time = 0;
		return ;
	}
	t_AbilityEffect add;
	add.duration = duration;
	add.time = 0;
	add.ability = ability;
	add.pos = pos;
	add.effect = NULL;
	CreateEffect(add);
	effects.push_back(add);
}

void EffectUpdater::UpdateEffect(t_AbilityEffect &effect)
{
	switch (effect.ability.type)
	{
		case SMOKE_BOMB:
		{
			SmokeEffect *used = (SmokeEffect*)effect.effect;
			used->Update();
			break ;
		}
	}
}

void EffectUpdater::DeleteEffect(void *effect, int type)
{
	switch (type)
	{
		case SMOKE_BOMB:
		{
			SmokeEffect* used = (SmokeEffect*)effect;
			delete used;
			break ;
		}
	}	
}

void EffectUpdater::CheckTurnCounter()
{
	if (gameState.updateObjs.turnOrder->turnCount == turnChecker)
		return ;
	turnChecker = gameState.updateObjs.turnOrder->turnCount;
	for (int i = 0; i < effects.size(); i++)
	{
		effects[i].time += 1;
		if (effects[i].time == effects[i].duration)
		{
			DeleteEffect(effects[i].effect, effects[i].ability.type);
			effects.erase(effects.begin() + i);
			i--;
		}
	}
}

void EffectUpdater::Update()
{
	CheckTurnCounter();
	for (int i = 0; i < effects.size(); i++)
		UpdateEffect(effects[i]);
}

void EffectUpdater::Clear()
{
	for (int i = 0; i < effects.size(); i++)
		DeleteEffect(effects[i].effect, effects[i].ability.type);
	effects.clear();
}
