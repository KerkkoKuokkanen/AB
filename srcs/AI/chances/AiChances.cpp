
#include "../../../hdr/global.h"

bool AiCheckSmoked(SDL_Point pos, t_AiMapUnit **map)
{
	bool smoke = std::get<0>(map[pos.y][pos.x].adds.smoke);
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

static int ChanceModifiers(t_AiCharacter *character, t_AiCharacter *target, int chance)
{
	return (chance);
}

static int SmokeChecker(t_AiCharacter *character, t_AiMapUnit **map, int chance)
{
	SDL_Point pos = character->position;
	if (!AiCheckSmoked(pos, map))
		return (chance);
	chance = rounding((float)chance * 0.5f);
	return (chance);
}

int AiGetChance(t_AiCharacter *character, t_AiCharacter *target, t_Ability *ability, t_AiMapUnit **map)
{
	int baseChance = GetTheBaseChance(character->character, target->character, ability);
	if (baseChance == 200)
		return (100);
	baseChance += AiRangedChance(character, target);
	baseChance = ChanceModifiers(character, target, baseChance);
	baseChance = (ability == NULL) ? baseChance : SmokeChecker(character, map, baseChance);
	if (baseChance > 95)
		baseChance = 95;
	if (baseChance < 5)
		baseChance = 5;
	return (baseChance);
}
