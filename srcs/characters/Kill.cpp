
#include "../../hdr/global.h"

Kill::Kill()
{
	killPart1 = gameState.textures.KillParticle[0];
	killPart2 = gameState.textures.KillParticle[1];
}

void Kill::Update()
{
	if (kills.size() == 0)
	{
		killing = false;
		return ;
	}
	killing = true;
	for (int i = 0; i < kills.size(); i++)
	{

		kills[i].timer--;
		if (kills[i].timer <= 0)
		{
			RemoveCharacter(kills[i].character);
			kills.erase(kills.begin() + i);
			i--;
		}
	}
}

void Kill::AddCharacterToKill(Character *character)
{
	t_kill kill = {character, KILL_TIME};
	character->killed = true;
	kills.push_back(kill);
}

void Kill::RemoveCharacter(Character *character)
{
	gameState.battle.ground->RemoveCharacter(character);
	Character *chosen = gameState.updateObjs.indicator->getChosen();
	if (chosen != NULL)
	{
		if (chosen == character)
			gameState.updateObjs.indicator->Deactivate();
	}
	gameState.updateObjs.turnOrder->RemoveCharacter(character);
	character->Destroy();
	//delete character; may need to be used later
}
