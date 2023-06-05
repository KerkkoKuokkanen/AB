
#include "../../hdr/global.h"

#define CAMERA_ARROW_MOVE_AMOUNT 10.0f

void ManageMouseWheel()
{
	if (gameState.keys.wheel > 0)
		gameState.keys.wheel -= 1;
	else if (gameState.keys.wheel < 0)
		gameState.keys.wheel += 1;
}

void ManageMouseClick()
{
	static int clickState = 0;
	if (clickState == 0 && gameState.keys.click == INITIAL_CLICK)
	{
		clickState = 1;
		return ;
	}
	if (clickState == 1 && gameState.keys.click == INITIAL_CLICK)
	{
		gameState.keys.click = HOLD_CLICK;
		return ;
	}
	if (clickState == 1 && gameState.keys.click == NO_CLICK)
	{
		clickState = 2;
		gameState.keys.click = RELEASE_CLICK;
		return ;
	}
	if (clickState == 2)
	{
		gameState.keys.click = NO_CLICK;
		clickState = 0;
	}
}

void CameraWithArrows()
{
	int xAxis = gameState.keys.right - gameState.keys.left;
	int yAxis = gameState.keys.down - gameState.keys.up;
	gameState.camera.x += rounding(((float)xAxis * CAMERA_ARROW_MOVE_AMOUNT) * gameState.screen.xPixelUnit);
	gameState.camera.y += rounding(((float)yAxis * CAMERA_ARROW_MOVE_AMOUNT) * gameState.screen.yPixelUnit / gameState.screen.aspectRatio);
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
	gameState.keys.staticMouseX = x;
	gameState.keys.staticMouseY = y;
	gameState.keys.smX = (int)((float)(x - gameState.screen.midPointX) * gameState.screen.xStaticUnit);
	gameState.keys.smY = (int)((float)(y - gameState.screen.midPointY) * gameState.screen.yStaticUnit);
	x = (int)((float)(x - gameState.screen.midPointX) * gameState.screen.xPixelUnit) + gameState.camera.x;
	y = (int)((float)(y - gameState.screen.midPointY) * gameState.screen.yPixelUnit / gameState.screen.aspectRatio) + gameState.camera.y;
	gameState.keys.mouseX = x;
	gameState.keys.mouseY = y;
}

void CheckOverMenu()
{
	static int middle = 0;
	gameState.updateObjs.hover.overAnything = false;
	gameState.updateObjs.hover.overCharacterUI = false;
	gameState.updateObjs.hover.overMenu = false;
	gameState.updateObjs.hover.overTurnOrder = false;
	if (gameState.updateObjs.turnOrder != NULL && gameState.updateObjs.turnOrder->insideBox)
		gameState.updateObjs.hover.overTurnOrder = true;
	if (gameState.updateObjs.UI != NULL && gameState.updateObjs.UI->overCharacterUI)
		gameState.updateObjs.hover.overCharacterUI = true;
	if (gameState.updateObjs.hover.overTurnOrder ||
		gameState.updateObjs.hover.overMenu ||
		gameState.updateObjs.hover.overCharacterUI ||
		gameState.updateObjs.hover.overCharacter ||
		middle != 0)
		gameState.updateObjs.hover.overAnything = true;
	if (gameState.keys.middleMouse != 0 && middle == 0)
		middle = 1;
	if (gameState.keys.middleMouse == 0)
		middle = 0;
}

void Utility()
{
	eventPoller();
	ManageMouseClick();
	CameraMove();
	CameraWithArrows();
	KeyCheck();
	GetMouseXY();
	ManageMouseWheel();
	ManageTextureHovering();
	CheckOverMenu();
}

void ObjUpdate()
{
	for (int i = 0; i < gameState.updateObjs.dusts.size(); i++)
		gameState.updateObjs.dusts[i]->Update();
	if (gameState.updateObjs.turnOrder != NULL)
		gameState.updateObjs.turnOrder->Update();
	gameState.updateObjs.indicator->Update();
	UpdateHoveredCharacter();
	if (gameState.updateObjs.UI->active)
		gameState.updateObjs.UI->Update();
	if (gameState.updateObjs.abilityManager != NULL)
		gameState.updateObjs.abilityManager->Update();
	if (gameState.updateObjs.animationManager != NULL)
		gameState.updateObjs.animationManager->Update();
	if (gameState.updateObjs.objectManager != NULL)
		gameState.updateObjs.objectManager->Update();
	if (gameState.updateObjs.groundColoring != NULL)
		gameState.updateObjs.groundColoring->Update();
	if (gameState.updateObjs.createDamage != NULL)
		gameState.updateObjs.createDamage->Update();
	gameState.updateObjs.killer->Update();
	gameState.updateObjs.partManager->Update();
	gameState.updateObjs.fadeIter += 0.06f;
	if (gameState.updateObjs.fadeIter >= 44.0f)
		gameState.updateObjs.fadeIter = 0.0f;
}
