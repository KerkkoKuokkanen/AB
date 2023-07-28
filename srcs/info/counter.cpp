
#include "../../hdr/global.h"

#define NUMBERS_Y -46550.0f
#define ALLIED_X -46720.0f
#define ENEMY_X -38250.0f
#define TURN_X -42400.0f
#define NUMBER_SIZE 1100
#define TURN_SIZE 1700

static void PositionNumber(Number *num, float x, bool turn = false)
{
	if (num == NULL)
		return ;
	x -= (float)num->getFullWidth() / 2.0f;
	float yAdd = 0.0f;
	if (turn)
		yAdd = 500.0f;
	num->Position(Vector(x, NUMBERS_Y - yAdd));
}

int Counter::GetAllies()
{
	int ret = 0;
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		if (gameState.battle.ground->characters[i].character->ally)
			ret++;
	}
	return (ret);
}

int Counter::GetEnemies()
{
	int ret = 0;
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		if (!gameState.battle.ground->characters[i].character->ally)
			ret++;
	}
	return (ret);
}

Counter::Counter()
{
	SDL_Rect dest = {-49000, -49300, 13000, 4400};
	sprite = new Sprite(gameState.textures.counter, dest, NULL, NULL, 0, FLIP_NONE, true);
	gameState.render->AddSprite(sprite, COUNTER_LAYER);
	allied = GetAllies();
	enemy = GetEnemies();
	currentTurn = 0;
	allies = new Number(allied, NUMBER_SIZE, COUNTER_LAYER, 2, true, NumberType::WHITE);
	enemies = new Number(enemy, NUMBER_SIZE, COUNTER_LAYER, 2, true, NumberType::WHITE);
	turn = new Number(currentTurn, TURN_SIZE, COUNTER_LAYER, 2, true, NumberType::WHITE);
	turn->ColorMod(31, 20, 1);
	enemies->ColorMod(255, 204, 115);
	allies->ColorMod(255, 204, 115);
	PositionNumber(allies, ALLIED_X);
	PositionNumber(enemies, ENEMY_X);
	PositionNumber(turn, TURN_X, true);
}

void Counter::ManageTurn()
{
	int turnNow = gameState.updateObjs.turnOrder->turnCount;
	if (currentTurn == turnNow)
		return ;
	currentTurn = turnNow;
	delete turn;
	turn = new Number(currentTurn, TURN_SIZE, COUNTER_LAYER, 2, true, NumberType::WHITE);
	turn->ColorMod(31, 20, 1);
	PositionNumber(turn, TURN_X, true);
}

void Counter::ManageAllies()
{
	int alliedNow = GetAllies();
	if (allied == alliedNow)
		return ;
	allied = alliedNow;
	delete allies;
	allies = new Number(allied, NUMBER_SIZE, COUNTER_LAYER, 2, true, NumberType::WHITE);
	allies->ColorMod(255, 204, 115);
	PositionNumber(allies, ALLIED_X);
}

void Counter::ManageEnemies()
{
	int enemiesNow = GetEnemies();
	if (enemy == enemiesNow)
		return ;
	enemy = enemiesNow;
	delete enemies;
	enemies = new Number(enemy, NUMBER_SIZE, COUNTER_LAYER, 2, true, NumberType::WHITE);
	enemies->ColorMod(255, 204, 115);
	PositionNumber(enemies, ENEMY_X);
}

void Counter::Update()
{
	ManageTurn();
	ManageAllies();
	ManageEnemies();
}

void Counter::Destroy()
{
	delete allies;
	delete enemies;
	delete turn;
	delete sprite;
}
