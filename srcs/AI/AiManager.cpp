
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

static void SetDataReady(t_BestMove &returned)
{
	std::unique_lock<std::mutex> lock(aiMotionMutex);
	move.ability = returned.ability;
	move.same = returned.same;
	move.score = returned.score;
	move.pos = returned.pos;
	move.character = returned.character;
	move.tPoints.clear();
	for (int i = 0; i < returned.tPoints.size(); i++)
		move.tPoints.push_back(returned.tPoints[i]);
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
	t_AiCharacter turn;
	GetTheStartingTurnForAi(&turn);
	float startSore = GetAiScore(map, turn.character->ally);
	AiIterator *used = new AiIterator;
	used->CalculateMoves(map, turn, startSore, 0);
	t_BestMove tester = used->GetBestMove();
	DeactivateAI();
	SetDataReady(tester);
	delete used;
	DestroyMap(map);
}

static bool GiveTurnToAi()
{
	if (gameState.updateObjs.turnOrder->turnStartActive ||
		gameState.updateObjs.turnOrder->turnChange)
		return (false);
	if (SomeOneMoving())
		return (false);
	if (gameState.updateObjs.abilities->active)
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
	if (ret.ability == NULL)
	{
		gameState.battle.ground->SetAiMoveAction(ret.pos, ret.character->character->position);
		return ;
	}
	gameState.updateObjs.abilities->SetAiAbilityToAction(ret.ability, ret.character->character, ret.pos, ret.tPoints);
}

void AiManaging() //this function is for the default thread for managing AI
{
	if (dataReady)
		HandleDataAction();
	if (GiveTurnToAi())
		SetAiInMotion();
}
