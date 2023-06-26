
#include "../../hdr/global.h"

void Abilities::SetSelector(t_Ability *ability, Character *character)
{
	SDL_Point pos = gameState.updateObjs.indicator->FindCharacter(character);
	switch(ability->type)
	{
		case DAGGER_THROW:
			selector = new Selector(pos, 13, 2, false, &groundColoring);
			break ;
	}
}

void Abilities::SetAbility(t_Ability *ability, Character *character)
{
	Abilities::ability = ability;
	Abilities::character = character;
	SetSelector(ability, character);
	active = true;
}

void Abilities::Upadte()
{
	if (selector != NULL)
	{
		Character *ret = selector->Update();
		if (ret != NULL)
			Clear();
	}
	groundColoring.Update();
	if (gameState.keys.rightClick == INITIAL_CLICK)
		Clear();
}

void Abilities::Clear()
{
	ability = NULL;
	character = NULL;
	if (selector != NULL)
		delete selector;
	selector = NULL;
	active = false;
	groundColoring.ClearMap();
}
