
#include "../../hdr/global.h"

void HealthColoring::Update()
{
	if (gameState.updateObjs.abilities->active)
		return ;
	counter++;
	if (counter % 100 != 0)
		return ;
	counter = 1;
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *ret = gameState.battle.ground->characters[i].character;
		if (ret->killed)
			continue ;
		int health = ret->stats.health; int maxH = ret->stats.maxHealth;
		maxH = (maxH == 0) ? maxH = 1 : maxH = maxH;
		float amount = (float)health / (float)maxH;
		if (amount > 0.25f)
			continue ;
		gameState.updateObjs.info->AddColorEffect(ret->sprite, 3, Color(255, 0, 0), 0);
		gameState.updateObjs.info->AddColorEffect(ret->sprite, 3, Color(255, 0, 0), 6);
	}
}
