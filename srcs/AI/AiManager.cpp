
#include "../../hdr/global.h"
#include <mutex>

bool dataReady = false;
bool aiInMotion = false;
t_BestMove move = {};

std::mutex aiMotionMutex;

void SetAiInMotion()
{
	std::unique_lock<std::mutex> lock(aiMotionMutex);
	aiInMotion = true;
	dataReady = false;
}

t_BestMove CollectData()
{
	std::unique_lock<std::mutex> lock(aiMotionMutex);
	t_BestMove ret = move;
	ret.same = move.same;
	move.same = false;
	dataReady = false;
	return (ret);
}

static void SetDataReady()
{
	std::unique_lock<std::mutex> lock(aiMotionMutex);
	move.same = true;
	dataReady = true;
}

static void DeactivateAI()
{
	std::unique_lock<std::mutex> lock(aiMotionMutex);
	aiInMotion = false;
}

void AiManagerUpdate()	//funtion only for the Ai thread
{
	if (aiInMotion == false)
		return ;
	t_AiMapUnit **map = GetTheMap();
	t_AiCharacter turn = GetTheStartingTurnForAi();
	float startSore = GetAiScore(map, turn.character->ally);
	SetDataReady();
	DeactivateAI();
	DestroyMap(map);
}

static bool GiveTurnToAi()
{
	if (gameState.updateObjs.turnOrder->turnStartActive ||
		gameState.updateObjs.turnOrder->turnChange)
		return (false);
	if (aiInMotion == true)
		return (false);
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *character = gameState.battle.ground->characters[i].character;
		if (character->turn && character->ally == false)
			return (true);
	}
	return (false);
}

static void HandleDataAction()
{
	t_BestMove ret = CollectData();
	if (ret.same)
	{
		gameState.updateObjs.turnOrder->ActivateTurnChange();
		return ;
	}
}

void AiManaging() //this function is for the default thread for managing AI
{
	if (dataReady)
		HandleDataAction();
	if (GiveTurnToAi())
		SetAiInMotion();
}
