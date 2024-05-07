
#include "../../hdr/global.h"
#include "../../hdr/render/camera.h"

void SetScreenShake(int volume, int time)
{
	gameCamera.screenShake.xShake = 0;
	gameCamera.screenShake.yShake = 0;
	gameCamera.screenShake.shakeCounter = time;
	gameCamera.screenShake.xShake = (rand() % 2 == 0) ? volume : -volume;
	gameCamera.screenShake.yShake = (rand() % 2 == 0) ? volume : -volume;
	gameCamera.screenShake.shakeVolume = volume;
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
	if (gameCamera.screenShake.shakeCounter <= 0)
	{
		gameCamera.screenShake.xShake = 0;
		gameCamera.screenShake.yShake = 0;
		return ;
	}
	gameCamera.screenShake.shakeCounter--;
	if (gameCamera.screenShake.xShake != 0)
	{
		gameCamera.screenShake.xShake = 0;
		gameCamera.screenShake.yShake = 0;
		return ;
	}
	if (cornerCycle == 0)
	{
		gameCamera.screenShake.xShake = -gameCamera.screenShake.shakeVolume;
		gameCamera.screenShake.yShake = -gameCamera.screenShake.shakeVolume;
	}
	else if (cornerCycle == 1)
	{
		gameCamera.screenShake.xShake = gameCamera.screenShake.shakeVolume;
		gameCamera.screenShake.yShake = -gameCamera.screenShake.shakeVolume;
	}
	else if (cornerCycle == 2)
	{
		gameCamera.screenShake.xShake = -gameCamera.screenShake.shakeVolume;
		gameCamera.screenShake.yShake = gameCamera.screenShake.shakeVolume;
	}
	else
	{
		gameCamera.screenShake.xShake = gameCamera.screenShake.shakeVolume;
		gameCamera.screenShake.yShake = gameCamera.screenShake.shakeVolume;
	}
	cornerCycle++;
	if (cornerCycle == 4)
		cornerCycle = 0;
}
