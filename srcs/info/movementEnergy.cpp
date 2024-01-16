
#include "../../hdr/global.h"

void MovementEnergy::Update()
{
	if (gameState.battle.ground->movedCharacter.character == NULL)
	{
		index = (-1);
		currEnergyUse = 0;
		return ;
	}
	int iter = gameState.battle.ground->movedCharacter.index;
	if (index != iter)
	{
		index = iter;
		SDL_Point pos = gameState.battle.ground->movedCharacter.path[index + 1];
		int cost = gameState.battle.ground->toolMap[pos.y][pos.x];
		int energy = cost - currEnergyUse;
		currEnergyUse += energy;
		int fat = energy * 1.5f + gameState.battle.ground->movedCharacter.character->stats.fatigue;
		if (fat > gameState.battle.ground->movedCharacter.character->stats.maxFatigue)
		{
			gameState.battle.ground->CancelMovement(gameState.battle.ground->movedCharacter.path[index]);
			return ;
		}
		if (gameState.battle.ground->movedCharacter.character->ally)
			gameState.updateObjs.UI->UseEnergy(energy, true);
		else
		{
			gameState.battle.ground->movedCharacter.character->moves -= energy;
			gameState.battle.ground->movedCharacter.character->stats.fatigue += energy * 1.5f;
		}
	}
}
