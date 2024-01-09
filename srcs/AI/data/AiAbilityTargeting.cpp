
#include "../../../hdr/global.h"

static bool CheckIfCanHit(t_AiMapUnit **map, t_Ability *ability, SDL_Point pos, SDL_Point start)
{
	t_TargetingType ret = GetAbilityTargetingType(ability);
	int range = ret.range;
	int dist = moveMaps.abilities[start.y][start.x].map[pos.y][pos.x];
	if (dist > range)
		return (false);
	if (map[pos.y][pos.x].obj.obj == true)
		return (false);
	if (map[pos.y][pos.x].character.character != NULL && ret.characters == false)
		return (false);
	if (ret.targetType == SelectorTypesForAi::SELECTOR && map[pos.y][pos.x].character.character == NULL)
		return (false);
	return (true);
}

void AiIterator::CheckForAbility(SDL_Point pos)
{
	for (int i = 0; i < character.character->abilities.size(); i++)
	{
		t_Ability *ability = &character.character->abilities[i];
		if (ability->cost > character.moves)
			continue ;
		if (!CheckIfCanHit(map, ability, pos, character.position))
			continue ;
		HandleAbilityAction(pos, ability);
	}
}

void AiIterator::HandleAbilityAction(SDL_Point pos, t_Ability *ability)
{
	t_AiMapUnit **newMap = GetReplica(map);
	UseTheAbility(pos, ability, newMap);
}

void AiIterator::UseTheAbility(SDL_Point pos, t_Ability *ability, t_AiMapUnit **newMap)
{
	int sign = ability->type;
	switch (sign)
	{
		case DAGGER_THROW:
		{
			
		}
	}
}
