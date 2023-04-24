
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
		float diffX = gameState.camera.clickTimePosX - x;
		float diffY = gameState.camera.clickTimePosY - y;
		gameState.camera.x += rounding(diffX * gameState.screen.xPixelUnit);
		gameState.camera.y += rounding(diffY * gameState.screen.yPixelUnit / gameState.screen.aspectRatio);
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
	gameState.screen.xPixelUnit = (1.0f / gameState.screen.unit) / gameState.screen.width;
	gameState.screen.yPixelUnit = (1.0f / gameState.screen.unit) / gameState.screen.height;
}

void KeyCheck()
{
	static int ss = 0;
	static int ww = 0;

	if (gameState.keys.s == 1 && ss == 0)
	{
		gameState.battle.ground->ChangeMapHeight(true);
		ss = 1;
	}
	if (gameState.keys.s == 0)
		ss = 0;
	if (gameState.keys.w == 1 && ww == 0)
	{
		gameState.battle.ground->ChangeMapHeight(false);
		ww = 1;
	}
	if (gameState.keys.w == 0)
		ww = 0;
}

int MainLoop(t_wr &wr)
{
	//gameState.battle.ground->CreateMap();
	clock_t start, end;
	Character thief;
	std::vector<Character> chars = {thief};
	SDL_Point point = {0, 0};
	std::vector<SDL_Point> pnt = {point};
	gameState.battle.ground->StartBattle(chars, pnt);

	while (1)
	{
		start = clock();
		eventPoller();
		CameraMove();
		KeyCheck();
		gameState.battle.ground->Update();
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