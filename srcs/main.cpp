
#include "../hdr/ab.h"
#include "../hdr/global.h"
#include <string>
#include <stdio.h>

t_GameState gameState;

void ManageMouseWheel()
{
	if (gameState.keys.wheel > 0)
		gameState.keys.wheel -= 1;
	else if (gameState.keys.wheel < 0)
		gameState.keys.wheel += 1;
}

void CameraMove()
{
	if (gameState.updateObjs.turnOrder->insideBox)
		return ;
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
		gameState.screen.unit *= 1.025f;
	else if (gameState.keys.wheel < 0)
		gameState.screen.unit *= 0.975f;
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
	Character thief3(THIEF);
	Character thief4(THIEF);
	Character skele3(SKELE, false);
	Character skele4(SKELE, false);
	Character skele5(SKELE, false);
	Character skele6(SKELE, false);
	static std::vector<Character> chars = {thief, thief2, skele, skele2, thief3, thief4, skele3, skele4, skele5, skele6};
	SDL_Point point = {8, 6};
	SDL_Point point2 = {3, 12};
	SDL_Point point3 = {9, 2};
	SDL_Point point4 = {8, 14};
	SDL_Point point5 = {7, 6};
	SDL_Point point6 = {2, 12};
	SDL_Point point7 = {9, 5};
	SDL_Point point8 = {1, 1};
	SDL_Point point9 = {0, 0};
	SDL_Point point10 = {3, 3};
	static std::vector<SDL_Point> pnt = {point, point2, point3, point4, point5, point6, point7, point8, point9, point10};
	gameState.battle.ground->StartBattle(chars, pnt);
	new TurnOrder(chars);
}

void ObjUpdate()
{
	for (int i = 0; i < gameState.updateObjs.dusts.size(); i++)
		gameState.updateObjs.dusts[i]->Update();
	if (gameState.updateObjs.indicator != NULL)
		gameState.updateObjs.indicator->Update();
	if (gameState.updateObjs.turnOrder != NULL)
		gameState.updateObjs.turnOrder->Update();
	if (gameState.updateObjs.killer != NULL)
		gameState.updateObjs.killer->Update();
	gameState.updateObjs.fadeIter += 0.06f;
	if (gameState.updateObjs.fadeIter >= 44.0f)
		gameState.updateObjs.fadeIter = 0.0f;
}

int MainLoop(t_wr &wr)
{
	clock_t start, end;
	TempInitBattle();
	bool killed = false;
	while (1)
	{
		start = clock();
		Utility();
		gameState.battle.ground->Update();
		if (gameState.keys.space == 1)
			gameState.updateObjs.turnOrder->ActivateTurnChange();
		ObjUpdate();
		gameState.render->RenderAll();
		ManageMouseWheel();
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