
#include "../hdr/ab.h"
#include "../hdr/global.h"
#include <string>
#include <stdio.h>

t_GameState gameState;

void CameraMove()
{
	if (gameState.keys.middleMouse == 1)
	{
		int x = 0, y = 0;
		SDL_GetMouseState(&x, &y);
		int diffX = gameState.camera.clickTimePosX - x;
		int diffY = gameState.camera.clickTimePosY - y;
		gameState.camera.x += diffX * gameState.screen.xPixelUnit;
		gameState.camera.y += diffY * gameState.screen.yPixelUnit;
		gameState.camera.clickTimePosX = x;
		gameState.camera.clickTimePosY = y;
	}
	if (gameState.keys.wheel == 0)
		return ;
	if (gameState.keys.wheel > 0)
	{
		gameState.screen.unit *= 1.025f;
		gameState.keys.wheel -= 1;
	}
	else if (gameState.keys.wheel < 0)
	{
		gameState.screen.unit *= 0.975f;
		gameState.keys.wheel += 1;
	}
}

int MainLoop(t_wr &wr)
{
	SDL_Event evnt;
	SDL_Rect rect = {-500, -500, 1000, 1000};
	SDL_Rect dect = {3000, 3000, 1000, 1000};
	SDL_Texture *textureGun = get_texture(wr.rend, "real_gun.png");
	Sprite gun(textureGun, rect, NULL, NULL, 0, FLIP_NONE, false);
	Sprite mun(textureGun, dect, NULL, NULL, 0, FLIP_NONE, false);
	gameState.render->AddSprite(&gun, 0);
	gameState.render->AddSprite(&mun, 0);
	clock_t start, end;

	while (1)
	{
		start = clock();
		eventPoller();
		CameraMove();
		gameState.render->RenderAll();
		end = clock();
		SDL_Delay(figure_the_delay(start, end));
	}

	return (0);
}

int main()
{
	t_wr wr;
	init(&wr);
	return (MainLoop(wr));
}