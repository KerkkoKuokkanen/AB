
#include "../../hdr/global.h"
#define DAMAGE_MINUS -300
#define TEXT_MINUS 1600
#define MINIMUM_SIZE 1400
#define MAXIMUM_SIZE 2200

static int orderLayer = 0;

static bool LeftOrRight(Character *damager, Character *target) //true for left
{
	SDL_Point dPos = damager->position;
	SDL_Point tPos = target->position;
	int test1 = getXToLeft(tPos);
	if (dPos.x <= test1)
		return (false);
	return (true);
}

static Vector GetDirection(bool left)
{
	if (left)
	{
		Vector dir(0.0f, -1.0f);
		int angleAdd = rand() % 15;
		int angle = (rand() % 2 == 0) ? -45 + angleAdd : -45 - angleAdd;
		float rads = (float)angle * (PI / 180.0f);
		vectorRotate(dir, rads);
		return (dir.Normalized());
	}
	Vector dir(0.0f, -1.0f);
	int angleAdd = rand() % 15;
	int angle = (rand() % 2 == 0) ? 45 + angleAdd : 45 - angleAdd;
	float rads = (float)angle * (PI / 180.0f);
	vectorRotate(dir, rads);
	return (dir.Normalized());
}

static int GetPrecentInDamage(Character *target, int totalDamage)
{
	int total = target->stats.maxHealth + target->stats.maxArmor;
	float portion = (float)totalDamage / (float)total;
	int ret = rounding(portion * 100.0f);
	if (ret > 100)
		ret = 100;
	return (ret);
}

static int GetSize(Character *target, int totalDamage)
{
	int precent = GetPrecentInDamage(target, totalDamage);
	if (precent < 3)
		return (MINIMUM_SIZE);
	if (precent >= 50)
		return (MAXIMUM_SIZE);
	float unit = (float)(MAXIMUM_SIZE - MINIMUM_SIZE) / 43.0f;
	float multi = (float)(precent - 3);
	int size = MINIMUM_SIZE + rounding(unit * multi);
	return (size);
}

int GetAmount(int size)
{
	int sizeUse = size - MINIMUM_SIZE;
	float unit = 60.0f / (float)(MAXIMUM_SIZE - MINIMUM_SIZE);
	float amount = 25.0f + unit * (float)sizeUse;
	return (rounding(amount));
}

static Color GetColor(int size)
{
	float div = (float)(MAXIMUM_SIZE - MINIMUM_SIZE);
	float gUnit = 255.0f / div;
	float bUnit = 255.0f / div;
	float multi = (float)(size - MINIMUM_SIZE);
	float gAdd = gUnit * multi;
	float bAdd = bUnit * multi;
	int r = 255;
	int g = rounding(255.0f - gAdd);
	int b = rounding(255.0f - bAdd);
	if (b < 0)
		b = 0;
	if (g < 0)
		g = 0;
	return (Color(r, g, b));
}

void CreateDamageSnippet(Character *damager, Character *target, int totalDamage, bool opportunity)
{
	SDL_Point pos = target->topMid;
	bool dirTest;
	if (!opportunity)
		dirTest = LeftOrRight(damager, target);
	else
		dirTest = (target->sprite->dest.x < damager->sprite->dest.x) ? true : false;
	SDL_Point start = {0, pos.y + DAMAGE_MINUS};
	start.x = (dirTest) ? -(rand() % 500 - 1000) : (rand() % 500 + 3000);
	SDL_Point use = {target->sprite->dest.x + start.x, target->sprite->dest.y + start.y};
	Vector dir = GetDirection(dirTest);
	int size = GetSize(target, totalDamage);
	std::string num = std::to_string(totalDamage);
	const char *text = num.c_str();
	int time = 90 + rand() % 20;
	FlyingSnippet *used = new FlyingSnippet(text, Vector((float)use.x, (float)use.y), dir, size, time);
	used->SetDrag(1.115f);
	int amount = GetAmount(size);
	used->SetAmount(amount);
	used->SetOrdering(orderLayer);
	float speed = (float)(rand() % 310 + 200);
	used->SetSpeed(speed);
	Color ret = GetColor(size);
	used->SetColor(ret.r, ret.g, ret.b);
	orderLayer += 2;
	if (orderLayer >= 2147483600)
		orderLayer = 0;
}

void CreateTextSnippet(Character *damager, Character *target, const char *text, int size, Color color)
{
	SDL_Point pos = target->topMid;
	bool dirTest = LeftOrRight(damager, target);
	SDL_Point start = {0, pos.y + TEXT_MINUS};
	std::string str(text);
	int len = str.length();
	int offset = size * len;
	start.x = (dirTest) ? -(rand() % 500 - 5000 + offset) : (rand() % 500 - 400 + offset);
	SDL_Point use = {target->sprite->dest.x + start.x, target->sprite->dest.y + start.y};
	Vector dir = GetDirection(dirTest);
	int time = 90 + rand() % 20;
	FlyingSnippet *used = new FlyingSnippet(text, Vector((float)use.x, (float)use.y), dir, size, time);
	used->SetDrag(1.12f);
	used->SetAmount(50);
	used->SetOrdering(orderLayer);
	float speed = (float)(rand() % 310 + 200);
	used->SetSpeed(speed);
	used->SetColor(color.r, color.g, color.b);
	orderLayer += 2;
	if (orderLayer >= 2147483600)
		orderLayer = 0;
}

void CreateMiss(SDL_Point damager, SDL_Point target, Character *targ, bool sound)
{
	if (sound)
		PlaySound(gameState.audio.whiff, Channels::WHIFF, 0);
	if (targ->statuses.stun != 0)
		return ;
	SDL_Rect dDest = gameState.battle.ground->getTileDest(damager);
	SDL_Rect tDest = gameState.battle.ground->getTileDest(target);
	SDL_Point direction = {tDest.x - dDest.x, tDest.y - dDest.y};
	Vector dir = Vector((float)direction.x, (float)direction.y).Normalized();
	CharacterMover *mover = new CharacterMover(targ, dir, 8, 8, 300.0f);
	gameState.updateObjs.abilities->AddMiss(mover);
	Character *character = gameState.battle.ground->map[damager.y][damager.x].character;
	Character *targetC = gameState.battle.ground->map[target.y][target.x].character;
	CreateTextSnippet(character, targetC, "MISS", 1000, Color(32, 153, 186));
}
