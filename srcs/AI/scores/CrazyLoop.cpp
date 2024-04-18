
#include "../../../hdr/global.h"

// (figure out the best way to check the relevant positions)
// -> position scores for character in terms of abilites and their range
// -> position score could for example have three parts like: offence, defence and utility
// (maybe try abilities in the current position MAYBE)
// -> move to different positions in terms of the score
//    if character cant reach these positions move to positions close to the best positions
// -> try abilities in the different positions
// -> final score is health scores and position scores combined

// Position score calcilation ideas:
// Get preferred distances to enemies for characters?
// Give points to positions in terms of how many abilities they can use in thath position
// each ability could have its own simple score giving algorithm in terms of the possible targets
// in positions where you can not use abilities give score in terms of the distance to those good positions
// Give positions defensive score in terms of how long the distance is for the enemies and
// what enemies can use abilities to that position

#define BIG_MINUS -99999.0f

static float AiGetDamageReduction(t_AiCharacter *damager, float damage)
{
	float damageRet = damage;
	float frenzyMulti = (damager->statuses.frenzy == 0) ? 1.0f : 1.55f;
	damageRet *= frenzyMulti;
	return (damageRet);
}

static SDL_FPoint GetBaseDamageAndFatiguePerEnergy(t_AiCharacter *character, t_Ability *ability, t_AiMapUnit **map)
{
	SDL_FPoint ret = {0.0f, 0.0f};
	if (ability->damage == 0)
		return (ret);
	int min = character->character->stats.baseDamageLow;
	int max = character->character->stats.baseDamageHigh;
	float mid = (float)(min + max) / 2.0f;
	t_Ability *used = ability;
	int cost = (used->cost == 0) ? 1 : used->cost;
	float damage = (float)used->damage / 100.0f;
	float expected = ((mid * damage) / (float)cost);
	expected = AiGetDamageReduction(character, expected);
	float fatigue = (float)ability->fatigue / (float)cost;
	int chance = AiGetChanceForCharOnly(character, ability, map);
	float chanceMulti = (float)chance / 100.0f;
	expected *= chanceMulti;
	ret = {expected, fatigue};
	return (ret);
}

static bool AiIsControlled(SDL_Point pos, bool ally, t_AiMapUnit **map)
{
	int left = AiGetXToLeft(pos);
	int right = AiGetXToRight(pos);
	SDL_Point positions[4] = {{left, pos.y + 1}, {left, pos.y - 1}, {right, pos.y + 1}, {right, pos.y - 1}};
	for (int i = 0; i < 4; i++)
	{
		if (!AiValidPos(positions[i]))
			continue ;
		t_AiCharacter *used = map[positions[i].y][positions[i].x].character;
		if (used == NULL)
			continue ;
		if (AiCheckSmoked(positions[i], map))
			continue ;
		if (used->character->ally != ally)
			return (true);
	}
	return (false);
}

static float GetCharacterDamageForPosition(t_AiCharacter *character, SDL_Point pos, t_AiMapUnit **map)
{
	float expected = BIG_MINUS;
	for (int i = 0; i < character->character->abilities.size(); i++)
	{
		t_Ability *ability = &character->character->abilities[i];
		if (ability->damage == 0)
			continue ;
		bool isControlled = AiIsControlled(character->position, character->character->ally, map);
		if (!ability->melee && isControlled)
			continue ;
		int abilityRange = ability->range;
		int range = NewRangeToPosChecker(map, pos, character->position, abilityRange);
		//printf("character %d, target pos, %d %d, range %d, position %d, %d\n\n", character->character->cSing, pos.x, pos.y, range, character->position.x, character->position.y);
		SDL_FPoint stats = GetBaseDamageAndFatiguePerEnergy(character, ability, map);
		int remainingFatigue = character->character->stats.maxFatigue - character->fatigue;
		int controlAdd = (isControlled) ? 2 : 0;
		int rangeCheck = (range - abilityRange <= 0) ? 0 : range - (abilityRange + isControlled);
		int useMulti = 10 - rangeCheck;	//we can expect them to have 10 energy just fine
		float amount = stats.x * (float)useMulti;
		float fat = (useMulti < 0) ? 0.0f : stats.y * (float)useMulti;
		float overFlow = (remainingFatigue - fat > 0.0f) ? 0.0f : (fat - remainingFatigue) / stats.y;
		amount = amount - (stats.x * overFlow);
		expected = (amount > expected) ? amount : expected;
	}
	return (expected);
}

static int GetBiggest(float one, float two, float three)
{
	if (one >= two && one >= three)
		return (0);
	if (two >= one && two >= three)
		return (1);
	return (2);
}

float GetPositionOffenceScore(SDL_Point pos, t_AiCharacter *character, t_AiMapUnit **map, std::vector<t_AiCharacter*> &charQ)
{
	std::tuple<SDL_Point, float> positions[3] = {{{-1, -1}, BIG_MINUS}, {{-1, -1}, BIG_MINUS}, {{-1, -1}, BIG_MINUS}};
	bool ally = character->character->ally;
	for (int i = 0; i < charQ.size(); i++)
	{
		if (charQ[i]->character->ally == ally)
			continue ;
		SDL_Point targPos = charQ[i]->position;
		float damage = GetCharacterDamageForPosition(character, targPos, map);
		int smallestIndex = 0;
		float smallestValue = std::get<1>(positions[0]);
		for (int j = 1; j < 3; j++)
		{
			float value = std::get<1>(positions[j]);
			if (value < smallestValue)
			{
				smallestIndex = j;
				smallestValue = value;
			}
		}
		if (damage > std::get<1>(positions[smallestIndex]))
		{
			std::get<0>(positions[smallestIndex]) = targPos;
			std::get<1>(positions[smallestIndex]) = damage;
		}
	}
	float offenceScore = 0.0f;
	int energys = 10;
	for (int i = 0; i < 3; i++)
	{
		int biggest = GetBiggest(std::get<1>(positions[0]), std::get<1>(positions[1]), std::get<1>(positions[2]));
		float damage = std::get<1>(positions[biggest]);
		SDL_Point check = std::get<0>(positions[biggest]);
		if (check.x == (-1))
			break ;
		int totalDoable = map[check.y][check.x].character->health + map[check.y][check.x].character->armor;
		damage = damage / 10.0f;
		if (totalDoable > (int)(damage * (float)energys))
		{
			offenceScore += (damage * (float)energys);
			break ;
		}
		int used = rounding((float)totalDoable / damage);
		offenceScore += totalDoable;
		energys -= used;
		std::get<1>(positions[biggest]) = BIG_MINUS;
	}
	return (offenceScore);
	//good stuff but not needed now
	/* int positionDistance = 0;
	if (character->character->stats.size == 0)
		positionDistance = RangeBetweenPositionsWithControls(map, character->position, pos, ally);
	else
		positionDistance = RangeBetweenPositions(map, character->position, pos);
	int currentDistance = moveMaps.abilities[character->position.y][character->position.x].map[pos.y][pos.x];
	int additionalEnergyUsed = positionDistance - currentDistance;
	if (additionalEnergyUsed <= 0)
		return (offenceScore);
	float minusMulti = (float)additionalEnergyUsed / 10.0f;
	float minus = fabs(minusMulti * offenceScore);
	offenceScore -= minus;
	return (offenceScore); */
}

float GetPositionScoresForCharacters(t_AiMapUnit **map, std::vector<t_AiCharacter*> &charQ)
{
	float allyScore = 0.0f;
	float enemyScore = 0.0f;
	//printf("\n\n\n");
	for (int i = 0; i < charQ.size(); i++)
	{
		SDL_Point pos = charQ[i]->position;
		findMovablesNormal(map, 80, pos);
		float offence = GetPositionOffenceScore(pos, charQ[i], map, charQ);
		float defence = 0.0f;
		float additional = 0.0f;
		//printf("score: %f,character: %d,position, %d, %d\n", offence, charQ[i]->character->cSing, pos.x, pos.y);
		if (charQ[i]->character->ally)
			allyScore += offence;
		else
			enemyScore += offence;
	}
	return (allyScore - enemyScore);
}

float CrazyLoopScore(t_AiMapUnit **map, std::vector<t_AiCharacter*> &charQ)
{
	OrderTheCharQ(charQ);
	RemoveTheDead(map, charQ);
	float ret = GetPositionScoresForCharacters(map, charQ);
	//ReturnMapPositionDistances({0, 0}, map, charQ[0], 2, true, 0, 0, charQ);
	return (ret);
}
