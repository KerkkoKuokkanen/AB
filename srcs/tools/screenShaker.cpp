
#include "../../hdr/global.h"

void SetScreenShake(int volume, int time)
{
	gameState.screenShake.shakeCounter = time;
	gameState.screenShake.xShake = (rand() % 2 == 0) ? volume : -volume;
	gameState.screenShake.yShake = (rand() % 2 == 0) ? volume : -volume;
	gameState.screenShake.shakeVolume = volume;
}

void ShakeTheScreen()
{
	if (gameState.screenShake.shakeCounter <= 0)
		return ;
	gameState.screenShake.shakeCounter--;
	if (gameState.screenShake.xShake != 0)
	{
		gameState.screenShake.xShake = 0;
		gameState.screenShake.yShake = 0;
		return ;
	}
	if (gameState.screenShake.xShake < 0)
		gameState.screenShake.xShake = gameState.screenShake.shakeVolume;
	else
		gameState.screenShake.xShake = -gameState.screenShake.shakeVolume;
	if (gameState.screenShake.yShake < 0)
		gameState.screenShake.yShake = gameState.screenShake.shakeVolume;
	else
		gameState.screenShake.yShake = -gameState.screenShake.shakeVolume;
}
