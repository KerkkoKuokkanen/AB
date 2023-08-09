
#include "../../hdr/global.h"

void SetScreenShake(int volume, int time)
{
	gameState.screenShake.xShake = 0;
	gameState.screenShake.yShake = 0;
	gameState.screenShake.shakeCounter = time;
	gameState.screenShake.xShake = (rand() % 2 == 0) ? volume : -volume;
	gameState.screenShake.yShake = (rand() % 2 == 0) ? volume : -volume;
	gameState.screenShake.shakeVolume = volume;
}

void ShakeTheScreen()
{
	static int everyThird = 0;
	static int cornerCycle = 0;
	everyThird++;
	if (everyThird % 2 != 0)
		return ;
	if (everyThird > 300)
		everyThird = 0;
	if (gameState.screenShake.shakeCounter <= 0)
	{
		gameState.screenShake.xShake = 0;
		gameState.screenShake.yShake = 0;
		return ;
	}
	gameState.screenShake.shakeCounter--;
	if (gameState.screenShake.xShake != 0)
	{
		gameState.screenShake.xShake = 0;
		gameState.screenShake.yShake = 0;
		return ;
	}
	if (cornerCycle == 0)
	{
		gameState.screenShake.xShake = -gameState.screenShake.shakeVolume;
		gameState.screenShake.yShake = -gameState.screenShake.shakeVolume;
	}
	else if (cornerCycle == 1)
	{
		gameState.screenShake.xShake = gameState.screenShake.shakeVolume;
		gameState.screenShake.yShake = -gameState.screenShake.shakeVolume;
	}
	else if (cornerCycle == 2)
	{
		gameState.screenShake.xShake = -gameState.screenShake.shakeVolume;
		gameState.screenShake.yShake = gameState.screenShake.shakeVolume;
	}
	else
	{
		gameState.screenShake.xShake = gameState.screenShake.shakeVolume;
		gameState.screenShake.yShake = gameState.screenShake.shakeVolume;
	}
	cornerCycle++;
	if (cornerCycle == 4)
		cornerCycle = 0;
}
