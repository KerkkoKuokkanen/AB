
#include "../hdr/ab.h"
#include "../hdr/global.h"
#include <string>
#include <stdio.h>

t_GameState gameState;

void CameraMove()
{
	int xMove = gameState.keys.a - gameState.keys.d;
	int yMove = gameState.keys.w - gameState.keys.s;

	gameState.camera.x += xMove * 25;
	gameState.camera.y += yMove * 25;
}

int MainLoop(t_wr &wr)
{
	SDL_Event evnt;
	SDL_Rect rect = {1000, 1000, 1000, 1000};
	SDL_Texture *textureGun = get_texture(wr.rend, "real_gun.png");
	Sprite gun(textureGun, rect, NULL, NULL, 0, FLIP_NONE, false);
	gameState.render->AddSprite(&gun, 0);
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