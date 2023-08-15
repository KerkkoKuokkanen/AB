
#include "../../hdr/global.h"

t_AbilityEffect *EffectUpdater::CheckForEffectAlready(int type, SDL_Point pos)
{
	for (int i = 0; i < effects.size(); i++)
	{
		if (effects[i].ability->type == type && effects[i].pos.x == pos.x && effects[i].pos.y == pos.y)
			return (&effects[i]);
	}
	return (NULL);
}

void EffectUpdater::CreateEffect(Character *character, t_AbilityEffect &add)
{
	switch (add.ability->type)
	{
		case SMOKE_BOMB:
			add.effect = new SmokeEffect(character, add.ability, add.pos);
			break ;
		case PHANTOM_KNIGHT:
			add.effect = new PhantomKnight(character, add.ability, add.pos);
			break ;
	}
}

void EffectUpdater::SetEffect(Character *character, SDL_Point pos, t_Ability *ability)
{
	t_AbilityEffect *check = CheckForEffectAlready(ability->type, pos);
	if (check != NULL)
	{
		CreateParticlesForSmokeEffect(pos);
		return ;
	}
	t_AbilityEffect add;
	add.ability = ability;
	add.pos = pos;
	add.effect = NULL;
	CreateEffect(character, add);
	effects.push_back(add);
}

void EffectUpdater::UpdateEffect(t_AbilityEffect &effect, int index)
{
	bool done = false;
	switch (effect.ability->type)
	{
		case SMOKE_BOMB:
		{
			SmokeEffect *used = (SmokeEffect*)effect.effect;
			used->Update();
			if (used->done)
			{
				delete used;
				effects.erase(effects.begin() + index);
			}
			break ;
		}
		case PHANTOM_KNIGHT:
		{
			PhantomKnight *use = (PhantomKnight*)effect.effect;
			use->Update();
			if (use->done)
			{
				if (!done)
				{
					PlaySound(gameState.audio.poof, Channels::POOF, 0);
					done = true;
				}
				delete use;
				effects.erase(effects.begin() + index);
			}
			break ;
		}
	}
}

void EffectUpdater::Update()
{
	for (int i = 0; i < effects.size(); i++)
		UpdateEffect(effects[i], i);
}

void EffectUpdater::DeleteEffect(t_AbilityEffect &effect)
{
	switch (effect.ability->type)
	{
		case SMOKE_BOMB:
		{
			SmokeEffect *use = (SmokeEffect*)effect.effect;
			delete use;
			break ;
		}
		case PHANTOM_KNIGHT:
		{
			PhantomKnight *use = (PhantomKnight*)effect.effect;
			delete use;
			break ;
		}
	}
}

void EffectUpdater::Clear()
{
	for (int i = 0; i < effects.size(); i++)
		DeleteEffect(effects[i]);
	effects.clear();
}
