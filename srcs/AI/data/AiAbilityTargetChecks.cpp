
#include "../../../hdr/global.h"

static int AiGetXToRight(SDL_Point pos)
{
	int modder = (pos.y % 2 == 0) ? 0 : 1;
	return (pos.x + modder);
}

static int AiGetXToLeft(SDL_Point pos)
{
	int modder = (pos.y % 2 == 0) ? -1 : 0;
	return (pos.x + modder);
}

static bool AiValidChecker(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	return (true);
}

static bool CheckForMeleePos(t_AiMapUnit **map, SDL_Point pos, bool ally)
{
	if (!AiValidChecker(pos))
		return (false);
	if (map[pos.y][pos.x].character == NULL)
		return (false);
	if (map[pos.y][pos.x].character->character->ally != ally)
		return (true);
	return (false);
}

static bool CheckForNotMelee(t_AiMapUnit **map, t_Ability *ability, SDL_Point pos, bool ally)
{
	if (ability->melee)
		return (false);
	int left = AiGetXToLeft(pos);
	int right = AiGetXToRight(pos);
	if (CheckForMeleePos(map, {left, pos.y - 1}, ally))
		return (true);
	if (CheckForMeleePos(map, {left, pos.y + 1}, ally))
		return (true);
	if (CheckForMeleePos(map, {right, pos.y - 1}, ally))
		return (true);
	if (CheckForMeleePos(map, {right, pos.y + 1}, ally))
		return (true);
	return (false);
}

static bool AdditionalChecks(t_AiMapUnit **map, t_Ability *ability, t_AiCharacter *character, SDL_Point pos, SDL_Point start)
{
	if (ability->type != SKELE_LUNGE)
		return (true);
	int left = AiGetXToLeft(pos);
	int right = AiGetXToRight(pos);
	SDL_Point checkPositions[4] = {{left, pos.y - 1}, {left, pos.y + 1}, {right, pos.y - 1}, {right, pos.y + 1}};
	for (int i = 0; i < 4; i++)
	{
		if (!AiValidChecker(checkPositions[i]))
			continue ;
		if (map[checkPositions[i].y][checkPositions[i].x].blocked == false)
			return (true);
	}
	return (false);
}

bool AiCheckIfCanHit(t_AiMapUnit **map, t_Ability *ability, t_AiCharacter *character, SDL_Point pos, SDL_Point start)
{
	t_TargetingType ret = GetAbilityTargetingType(ability);
	int range = ret.range;
	int dist = 10000;
	if (!ret.staticSearch)
		dist = moveMaps.abilities[start.y][start.x].map[pos.y][pos.x];
	else
		dist = moveMaps.staticMoves[start.y][start.x].map[pos.y][pos.x];
	if (dist > range)
		return (false);
	if (map[pos.y][pos.x].obj.obj == true)
		return (false);
	if (CheckForNotMelee(map, ability, character->position, character->character->ally))
		return (false);
	if (map[pos.y][pos.x].character != NULL && ret.characters == false)
		return (false);
	if (ret.targetType == SelectorTypesForAi::SELECTOR && map[pos.y][pos.x].character == NULL)
		return (false);
	if (ret.targetType == SelectorTypesForAi::SELECTOR && map[pos.y][pos.x].character->alive == false)
		return (false);
	if (!AdditionalChecks(map, ability, character, pos, start))
		return (false);
	return (true);
}
