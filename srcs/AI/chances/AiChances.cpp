
#include "../../../hdr/global.h"

bool AiCheckSmoked(SDL_Point pos, t_AiMapUnit **map)
{
	bool smoke = map[pos.y][pos.x].adds.smoke.isIt;
	if (smoke)
		return (true);
	return (false);
}

static int GetTheBaseChance(Character *character, Character *target, t_Ability *ability)
{
	int baseChance = 0;
	if (ability == NULL)
	{
		baseChance = 50;
		int levelDiff = character->stats.level - target->stats.level;
		baseChance += 5 * levelDiff;
	}
	else
	{
		if (ability->baseChance >= 200)
			return (200);
		baseChance = ability->baseChance;
	}
	return (baseChance);
}

static int AiRangedChance(t_AiCharacter *character, t_AiCharacter *target)
{
	SDL_Point cPos = character->position;
	SDL_Point tPos = target->position;
	int height = gameState.battle.ground->map[cPos.y][cPos.x].height - gameState.battle.ground->map[tPos.y][tPos.x].height;
	if (height > 3)
		height = 3;
	if (height < -3)
		height = -3;
	return (5 * height);
}

static float AccBuffMulit(t_AiCharacter *character)
{
	float ret = 1.0f;
	for (int i = 0; i < character->statuses.buffs.size(); i++)
	{
		if (character->statuses.buffs[i].type == BuffTypes::ACCURACY)
			ret += (float)character->statuses.buffs[i].amount / 100.0f;
	}
	return (ret);
}

static float AccDeBuffMulti(t_AiCharacter *character)
{
	float ret = 1.0f;
	for (int i = 0; i < character->statuses.deBuffs.size(); i++)
	{
		if (character->statuses.deBuffs[i].type == BuffTypes::ACCURACY)
			ret -= (float)character->statuses.deBuffs[i].amount / 100.0f;
	}
	if (ret < 0.1f)
		ret = 0.1f;
	return (ret);
}

static int ChanceModifiers(t_AiCharacter *character, t_AiCharacter *target, int chance)
{
	float chanceRet = (float)chance;
	float accBuff = AccBuffMulit(character);
	float hostMulti = (character->statuses.hosted) ? 0.85f : 1.0f;
	float accDebuff = AccDeBuffMulti(character);
	chanceRet *= accBuff;
	chanceRet *= accDebuff;
	chanceRet *= hostMulti;
	return (rounding(chanceRet));
}

static int ChanceModifiersSolo(t_AiCharacter *character, int chance)
{
	float chanceRet = (float)chance;
	float accBuff = AccBuffMulit(character);
	float hostMulti = (character->statuses.hosted) ? 0.85f : 1.0f;
	float accDebuff = AccDeBuffMulti(character);
	chanceRet *= accBuff;
	chanceRet *= accDebuff;
	chanceRet *= hostMulti;
	return (rounding(chanceRet));
}

static int SmokeChecker(t_AiCharacter *character, t_AiMapUnit **map, int chance)
{
	SDL_Point pos = character->position;
	if (!AiCheckSmoked(pos, map))
		return (chance);
	chance = rounding((float)chance * 0.5f);
	return (chance);
}

static int CheckOppChancers(t_AiCharacter *character, t_Ability *ability, int ret)
{
	if (ability != NULL)
		return (ret);
	float multi = 1.0f;
	float chanceRet = (float)ret;
	for (int i = 0; i < character->statuses.buffs.size(); i++)
	{
		if (character->statuses.buffs[i].type == BuffTypes::OPPORTUNITY_ACCURACY)
			multi += (float)character->statuses.buffs[i].amount / 100.0f;
	}
	chanceRet *= multi;
	return (rounding(chanceRet));
}

int AiGetChance(t_AiCharacter *character, t_AiCharacter *target, t_Ability *ability, t_AiMapUnit **map)
{
	int baseChance = GetTheBaseChance(character->character, target->character, ability);
	if (baseChance == 200)
		return (100);
	baseChance += AiRangedChance(character, target);
	baseChance = ChanceModifiers(character, target, baseChance);
	baseChance = CheckOppChancers(character, ability, baseChance);
	baseChance = (ability == NULL) ? baseChance : SmokeChecker(character, map, baseChance);
	if (baseChance > 95)
		baseChance = 95;
	if (baseChance < 5)
		baseChance = 5;
	return (baseChance);
}

static bool CheckInItems(t_AiMapItem **items, SDL_Point pos)
{
	for (int i = 0; items[i] != NULL; i++)
	{
		if (items[i]->type != SMOKE_BOMB)
			continue ;
		SDL_Point check = items[i]->position;
		if (check.x == pos.x && check.y == pos.y)
			return (true);
	}
	return (false);
}

static bool IsControlledForSmoke(t_AiCharacter **charQ, SDL_Point pos, bool ally)
{
	for (int i = 0; charQ[i] != NULL; i++)
	{
		if (charQ[i]->character->ally == ally)
			continue ;
		SDL_Point check = charQ[i]->position;
		int dist = moveMaps.staticMoves[check.y][check.x].map[pos.y][pos.x];
		if (dist <= 2)
			return (true);
	}
	return (false);
}

static bool TargetsInRangeOfAbility(int range, t_AiCharacter *character, t_AiCharacter **charQ)
{
	bool ally = character->character->ally;
	SDL_Point pos = character->position;
	for (int i = 0; charQ[i] != NULL; i++)
	{
		if (charQ[i]->character->ally == ally)
			continue ;
		SDL_Point check = charQ[i]->position;
		int dist = moveMaps.abilities[pos.y][pos.x].map[check.y][check.x];
		if (dist <= range)
			return (true);
	}
	return (false);
}

static int CrazyLoopSmokeChecker(t_Ability *ability, t_AiCharacter *character, int chance, t_AiCharacter **charQ, t_AiMapItem **items)
{
	SDL_Point pos = character->position;
	if (CheckInItems(items, pos) == false)
		return (chance);
	if (IsControlledForSmoke(charQ, pos, character->character->ally))
		return (rounding((float)chance * 0.5f));
	if (TargetsInRangeOfAbility(ability->range, character, charQ))
		return (rounding((float)chance * 0.94f));
	return (chance);
}

int AiGetChanceForCharOnly(t_AiCharacter *character, t_Ability *ability, t_AiCharacter **charQ, t_AiMapItem **items)
{
	int baseChance = ability->baseChance;
	if (baseChance == 200)
		return (100);
	baseChance = ChanceModifiersSolo(character, baseChance);
	baseChance = CrazyLoopSmokeChecker(ability, character, baseChance, charQ, items);
	if (baseChance > 95)
		baseChance = 95;
	if (baseChance < 5)
		baseChance = 5;
	return (baseChance);
}
