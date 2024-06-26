
#include "../../hdr/global.h"
#define DAMAGE_MINUS -300
#define TEXT_MINUS 1600
#define MINIMUM_SIZE 1400
#define MAXIMUM_SIZE 2200

static int orderLayer = 0;

static bool LeftOrRight(SDL_Point damager, SDL_Point target) //true for left
{
	SDL_Point dPos = damager;
	SDL_Point tPos = target;
	int test1 = getXToLeft(tPos);
	if (dPos.x <= test1)
		return (false);
	return (true);
}

static Vector GetTextDirection(bool left)
{
	if (left)
	{
		Vector dir(0.0f, -1.0f);
		int angle = -75;
		float rads = (float)angle * (PI / 180.0f);
		vectorRotate(dir, rads);
		return (dir.Normalized());
	}
	Vector dir(0.0f, -1.0f);
	int angle = 75;
	float rads = (float)angle * (PI / 180.0f);
	vectorRotate(dir, rads);
	return (dir.Normalized());
}

static Vector GetDirection(bool left)
{
	int value = orderLayer / 2;
	int unit = value % 3;
	int angle = 0;
	switch (unit)
	{
		case 0:
			angle = 52;
			break ;
		case 1:
			angle = 62;
			break ;
		case 2:
			angle = 72;
			break ;
	}
	if (left)
	{
		Vector dir(0.0f, -1.0f);
		angle *= -1;
		float rads = (float)angle * (PI / 180.0f);
		vectorRotate(dir, rads);
		return (dir.Normalized());
	}
	Vector dir(0.0f, -1.0f);
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
	float unit = 30.0f / (float)(MAXIMUM_SIZE - MINIMUM_SIZE);
	float amount = 55.0f + unit * (float)sizeUse;
	return (rounding(amount));
}

static SDL_Point GetSnippetStart(bool dirTest, Character *target)
{
	int value = orderLayer / 2;
	int unit = value % 3;
	switch (unit)
	{
		case 0:
		{
			SDL_Point pos = target->topMid;
			SDL_Point start = {0, pos.y + DAMAGE_MINUS};
			start.x = (dirTest) ? -(rand() % 500 - 1000) : (rand() % 500 + 3500);
			SDL_Point use = {target->sprite->dest.x + start.x, target->sprite->dest.y + start.y};
			return (use);
		}
		case 1:
		{
			SDL_Point pos = target->topMid;
			SDL_Point start = {0, pos.y + 650};
			start.x = (dirTest) ? -(rand() % 500 - 1000) : (rand() % 500 + 3500);
			SDL_Point use = {target->sprite->dest.x + start.x, target->sprite->dest.y + start.y};
			return (use);
		}
		case 2:
		{
			SDL_Point pos = target->topMid;
			SDL_Point start = {0, pos.y + 1600};
			start.x = (dirTest) ? -(rand() % 500 - 1000) : (rand() % 500 + 3500);
			SDL_Point use = {target->sprite->dest.x + start.x, target->sprite->dest.y + start.y};
			return (use);
		}
	}
	SDL_Point ret = {0, 0};
	return (ret);
}

void CreatePoisonSnippet(Character *target, int totalAmount, Color color)
{
	bool dirTest = target->ally;
	SDL_Point use = GetSnippetStart(dirTest, target);
	Vector dir = GetDirection(dirTest);
	int size = GetSize(target, totalAmount);
	std::string num = std::to_string(totalAmount);
	const char *text = num.c_str();
	int time = 90 + rand() % 20;
	FlyingSnippet *used = new FlyingSnippet(text, Vector((float)use.x, (float)use.y), dir, size, time);
	used->SetDrag(1.115f);
	int amount = GetAmount(size);
	used->SetAmount(amount);
	used->SetOrdering(orderLayer);
	float speed = (float)(rand() % 50 + 290);
	used->SetSpeed(speed);
	used->SetColor(color.r, color.g, color.b);
	orderLayer += 2;
	if (orderLayer >= 2147483600)
		orderLayer = 0;
}

static bool LeftOrRightForOpp(SDL_Point damager, Character *target) //true for left
{
	t_GMU *used = &gameState.battle.ground->map[damager.y][damager.x];
	if (used->character != NULL)
	{
		bool ret = (target->sprite->dest.x < used->character->sprite->dest.x) ? true : false;
		return (ret);
	}
	if (used->additional.object != NULL && used->additional.type == AdditionalObjects::PHANTOM_KNIGHT)
	{
		PhantomKnight *ret = (PhantomKnight*)used->additional.object;
		Sprite *data = ret->GetSprite();
		bool value = (target->sprite->dest.x < data->dest.x) ? true : false;
		return (value);
	}
	return (false);
}

void CreateDamageSnippet(SDL_Point damager, Character *target, int totalDamage, bool opportunity)
{
	bool dirTest;
	if (!opportunity)
		dirTest = LeftOrRight(damager, target->position);
	else
		dirTest = LeftOrRightForOpp(damager, target);
	SDL_Point use = GetSnippetStart(dirTest, target);
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
	float speed = (float)(rand() % 50 + 290);
	used->SetSpeed(speed);
	Color ret(204, 60, 41);
	used->SetColor(ret.r, ret.g, ret.b);
	orderLayer += 2;
	if (orderLayer >= 2147483600)
		orderLayer = 0;
}

void CreateDamageSnippetWithColor(SDL_Point damager, Character *target, int totalDamage, Color col, bool opportunity)
{
	SDL_Point pos = target->topMid;
	bool dirTest;
	if (!opportunity)
		dirTest = LeftOrRight(damager, target->position);
	else
		dirTest = LeftOrRightForOpp(damager, target);
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
	float speed = (float)(rand() % 50 + 290);
	used->SetSpeed(speed);
	used->SetColor(col.r, col.g, col.b);
	orderLayer += 2;
	if (orderLayer >= 2147483600)
		orderLayer = 0;
}

void CreateTextSnippet(Character *damager, Character *target, const char *text, int size, Color color)
{
	SDL_Point pos = target->topMid;
	bool dirTest = LeftOrRight(damager->position, target->position);
	SDL_Point start = {3000, pos.y + TEXT_MINUS};
	std::string str(text);
	int len = str.length();
	int offset = ((size * 0.5f) * len);
	start.x = (dirTest) ? start.x - offset : start.x;
	SDL_Point use = {target->sprite->dest.x + start.x, target->sprite->dest.y + start.y};
	Vector dir = GetTextDirection(dirTest);
	int time = 90 + rand() % 20;
	FlyingSnippet *used = new FlyingSnippet(text, Vector((float)use.x, (float)use.y), dir, size, time);
	used->SetDrag(1.12f);
	used->SetAmount(50);
	used->SetOrdering(orderLayer);
	float speed = (float)(rand() % 50 + 290);
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
