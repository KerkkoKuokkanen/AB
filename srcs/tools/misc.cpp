
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
