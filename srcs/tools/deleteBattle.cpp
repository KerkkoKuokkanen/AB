
#include "../../hdr/ab.h"
#include "../../hdr/global.h"
#include "../../hdr/render/camera.h"

void RidDusts()
{
	for (int i = 0; i < gameState.updateObjs.dusts.size(); i++)
	{
		gameState.updateObjs.dusts[i]->SimpleClear();
		delete gameState.updateObjs.dusts[i];
	}
	gameState.updateObjs.dusts.clear();
}

void DeleteBattle()
{
	RidDusts();
	StopAiThread();
	ClearObjHolder();
	DeleteMoveMaps();
	delete gameState.updateObjs.indicator;
	gameState.updateObjs.indicator = NULL;
	delete gameState.updateObjs.killer;
	gameState.updateObjs.killer = NULL;
	delete gameState.updateObjs.partManager;
	gameState.updateObjs.partManager = NULL;
	delete gameState.updateObjs.UI;
	gameState.updateObjs.UI = NULL;
	delete gameState.updateObjs.abilities;
	gameState.updateObjs.abilities = NULL;
	delete gameState.updateObjs.info;
	gameState.updateObjs.info = NULL;
	delete gameState.updateObjs.turnOrder;
	gameState.updateObjs.turnOrder = NULL;
	delete gameState.updateObjs.objUpdate;
	gameState.updateObjs.objUpdate = NULL;
	delete gameState.backGround;
	gameState.backGround = NULL;
	delete gameState.filter;
	gameState.filter = NULL;
	delete gameState.battle.ground;
	gameState.battle.ground = NULL;
	gameState.render->RemoveAll();
}
