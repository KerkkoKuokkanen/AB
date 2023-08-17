
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
		gameState.updateObjs.UI->UseEnergy(energy);
	}
}
