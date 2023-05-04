
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

void GetMouseXY()
{
	int x = 0, y = 0;
	SDL_GetMouseState(&x, &y);
	x = (int)((float)(x - gameState.screen.midPointX) * gameState.screen.xPixelUnit) + gameState.camera.x;
	y = (int)((float)(y - gameState.screen.midPointY) * gameState.screen.yPixelUnit / gameState.screen.aspectRatio) + gameState.camera.y;
	gameState.keys.mouseX = x;
	gameState.keys.mouseY = y;
}

void Utility()
{
	eventPoller();
	CameraMove();
	KeyCheck();
	GetMouseXY();
}

void TempInitBattle()
{
	Character thief(THIEF);
	Character thief2(THIEF);
	Character skele(SKELE, false);
	Character skele2(SKELE, false);
	static std::vector<Character> chars = {thief, thief2, skele, skele2};
	SDL_Point point = {8, 6};
	SDL_Point point2 = {3, 12};
	SDL_Point point3 = {9, 2};
	SDL_Point point4 = {8, 14};
	static std::vector<SDL_Point> pnt = {point, point2, point3, point4};
	gameState.battle.ground->StartBattle(chars, pnt);
}

void ObjUpdate()
{
	for (int i = 0; i < gameState.updateObjs.dusts.size(); i++)
		gameState.updateObjs.dusts[i]->Update();
}

int MainLoop(t_wr &wr)
{
	clock_t start, end;
	TempInitBattle();
	while (1)
	{
		start = clock();
		Utility();
		gameState.battle.ground->Update();
		ObjUpdate();
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
	MainLoop(wr);
	return (0);
}