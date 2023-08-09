
#include "../../hdr/global.h"

static Character *FindTheCharacter()
{
	if (gameState.updateObjs.turnOrder->turnChange ||
		gameState.updateObjs.turnOrder->turnStartActive)
		return (NULL);
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *targ = gameState.battle.ground->characters[i].character;
		if (targ->turn)
			return (targ);
	}
	return (NULL);
}

static void ManageStatuses(Character *character)
{
	if (character == NULL)
		return ;
	t_StatusEffects &statuses = character->statuses;
	for (int i = 0; i < statuses.burns.size(); i++)
	{
		statuses.burns[i] -= 1;
		if (statuses.burns[i] <= 0)
		{
			statuses.burns.erase(statuses.burns.begin() + i);
			if (i != 0)
				i -= 1;
		}
	}
	if (statuses.stun > 0)
	{
		statuses.stun -= 1;
		gameState.updateObjs.turnOrder->ActivateTurnChange();
	}
}

void UpdateStatuses()
{
	static Character *current = NULL;
	Character *ret = FindTheCharacter();
	if (current != ret)
	{
		current = ret;
		if (current == NULL)
			return ;
		ManageStatuses(current);
	}
}
