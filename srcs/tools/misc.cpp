
#include "../../hdr/global.h"

bool CheckForTurnChange()
{
	if (gameState.keys.space != 1)
		return (false);
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *character = gameState.battle.ground->characters[i].character;
		if (character->turn && character->ally == false)
			return (false);
	}
	return(true);
}

bool SomeOneMoving()
{
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *used = gameState.battle.ground->characters[i].character;
		if (used->moving)
			return (true);
		if (used->damaged)
			return (true);
	}
	return (false);
}
