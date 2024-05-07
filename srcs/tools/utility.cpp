
#include "../../hdr/global.h"
#include "../../hdr/render/camera.h"

#define CAMERA_ARROW_MOVE_AMOUNT 10.0f

void ManageMouseWheel()
{
	if (gameState.keys.wheel > 0)
		gameState.keys.wheel -= 1;
	else if (gameState.keys.wheel < 0)
		gameState.keys.wheel += 1;
}

void FilterMode()
{
	static int shiftPress = 0;
	if (shiftPress == 0 && gameState.keys.shift != 0)
	{
		shiftPress = 1;
		gameState.modes.filterMode += 1;
	}
	if (shiftPress == 1 && gameState.keys.shift == 0)
		shiftPress = 0;
	if (gameState.modes.filterMode > 1)
		gameState.modes.filterMode = 0;
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
	gameCamera.x += rounding(((float)xAxis * CAMERA_ARROW_MOVE_AMOUNT) * gameCamera.screen.xPixelUnit);
	gameCamera.y += rounding(((float)yAxis * CAMERA_ARROW_MOVE_AMOUNT) * gameCamera.screen.yPixelUnit / gameCamera.screen.aspectRatio);
}

void CameraMove()
{
	if (gameState.updateObjs.turnOrder->insideBox)
		return ;
	if (gameState.keys.middleMouse == 1)
	{
		int x = 0, y = 0;
		SDL_GetMouseState(&x, &y);
		float diffX = gameCamera.clickTimePosX - x;
		float diffY = gameCamera.clickTimePosY - y;
		gameCamera.x += rounding(diffX * gameCamera.screen.xPixelUnit);
		gameCamera.y += rounding(diffY * gameCamera.screen.yPixelUnit / gameCamera.screen.aspectRatio);
		gameCamera.clickTimePosX = x;
		gameCamera.clickTimePosY = y;
	}
	if (gameState.keys.wheel == 0)
		return ;
	if (gameState.keys.wheel > 0)
		gameCamera.screen.unit *= 1.025f;
	else if (gameState.keys.wheel < 0)
		gameCamera.screen.unit *= 0.975f;
	gameCamera.screen.xPixelUnit = (1.0f / gameCamera.screen.unit) / gameCamera.screen.width;
	gameCamera.screen.yPixelUnit = (1.0f / gameCamera.screen.unit) / gameCamera.screen.height;
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
	gameState.keys.smX = (int)((float)(x - gameCamera.screen.midPointX) * gameCamera.screen.xStaticUnit);
	gameState.keys.smY = (int)((float)(y - gameCamera.screen.midPointY) * gameCamera.screen.yStaticUnit);
	x = (int)((float)(x - gameCamera.screen.midPointX) * gameCamera.screen.xPixelUnit) + gameCamera.x;
	y = (int)((float)(y - gameCamera.screen.midPointY) * gameCamera.screen.yPixelUnit / gameCamera.screen.aspectRatio) + gameCamera.y;
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
	gameState.updateObjs.hover.overAnythingButCharacter = false;
	if (gameState.updateObjs.turnOrder != NULL && gameState.updateObjs.turnOrder->insideBox)
		gameState.updateObjs.hover.overTurnOrder = true;
	if (gameState.updateObjs.info != NULL && gameState.updateObjs.info->overInfo)
		gameState.updateObjs.hover.overTurnOrder = true;
	if (gameState.updateObjs.info != NULL && gameState.updateObjs.info->overInfoBar)
		gameState.updateObjs.hover.overTurnOrder = true;
	if (gameState.updateObjs.UI != NULL && gameState.updateObjs.UI->overCharacterUI)
		gameState.updateObjs.hover.overCharacterUI = true;
	if (gameState.updateObjs.hover.overTurnOrder ||
		gameState.updateObjs.hover.overMenu ||
		gameState.updateObjs.hover.overCharacterUI ||
		gameState.updateObjs.hover.overCharacter ||
		middle != 0)
		gameState.updateObjs.hover.overAnything = true;
	if (gameState.updateObjs.hover.overTurnOrder ||
		gameState.updateObjs.hover.overMenu ||
		gameState.updateObjs.hover.overCharacterUI ||
		middle != 0)
		gameState.updateObjs.hover.overAnythingButCharacter = true;
	if (gameState.keys.middleMouse != 0 && middle == 0)
		middle = 1;
	if (gameState.keys.middleMouse == 0)
		middle = 0;
}

void SetDelayer(int delayAddition)
{
	if (gameState.delayer < delayAddition)
		gameState.delayer = delayAddition;
}

static void ManageDelay()
{
	if (gameState.delayer > 0)
		gameState.delayer -= 1;
}

void Utility()
{
	eventPoller(gameState.keys, gameCamera.clickTimePosX, gameCamera.clickTimePosY);
	FilterMode();
	ManageMouseClick();
	CameraMove();
	CameraWithArrows();
	KeyCheck();
	GetMouseXY();
	ManageMouseWheel();
	ManageTextureHovering();
	CheckOverMenu();
	ManageDelay();
	gameState.updateObjs.UI->ClearEnergys();
}

void DelayUpdate()
{
	gameState.battle.ground->Update();
	if (gameState.updateObjs.turnOrder != NULL)
		gameState.updateObjs.turnOrder->Update();
	gameState.updateObjs.indicator->Update();
	UpdateStatuses();
	if (gameState.updateObjs.UI->active)
		gameState.updateObjs.UI->Update();
	if (gameState.updateObjs.info != NULL)
		gameState.updateObjs.info->Update();
	if (gameState.updateObjs.objUpdate != NULL)
		gameState.updateObjs.objUpdate->Update();
	UpdateHoveredCharacter();
}

void ObjUpdate()
{
	if (gameState.delayer > 0)
		return (DelayUpdate());
	ShakeTheScreen();
	gameState.battle.ground->Update();
	for (int i = 0; i < gameState.updateObjs.dusts.size(); i++)
		gameState.updateObjs.dusts[i]->Update();
	if (gameState.updateObjs.turnOrder != NULL)
		gameState.updateObjs.turnOrder->Update();
	if (gameState.updateObjs.abilities != NULL)
		gameState.updateObjs.abilities->Upadte();
	gameState.updateObjs.indicator->Update();
	UpdateStatuses();
	if (gameState.updateObjs.UI->active)
		gameState.updateObjs.UI->Update();
	gameState.updateObjs.killer->Update();
	gameState.updateObjs.partManager->Update();
	if (gameState.updateObjs.info != NULL)
		gameState.updateObjs.info->Update();
	if (gameState.updateObjs.objUpdate != NULL)
		gameState.updateObjs.objUpdate->Update();
	gameState.updateObjs.fadeIter += 0.06f;
	gameState.updateObjs.characterAnimIter += 1;
	if (gameState.updateObjs.fadeIter >= 44.0f)
		gameState.updateObjs.fadeIter = 0.0f;
	if (gameState.updateObjs.characterAnimIter > 50)
	{
		gameState.updateObjs.characterAnimIndex = (gameState.updateObjs.characterAnimIndex == 0) ? 1 : 0;
		gameState.updateObjs.characterAnimIter = 0;
	}
	UpdateHoveredCharacter();
}
