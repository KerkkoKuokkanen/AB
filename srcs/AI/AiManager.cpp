
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

void CollectData()
{
	std::unique_lock<std::mutex> lock(aiMotionMutex);
	move.same = false;
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
}
