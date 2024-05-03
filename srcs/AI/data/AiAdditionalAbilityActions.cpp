
#include "../../../hdr/global.h"

static bool AiValidChecker(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	return (true);
}

void AiIterator::AdditionalActions(SDL_Point pos, t_Ability *ability, t_AiMapUnit **map)
{
	int left = AiGetXToLeft(pos);
	int right = AiGetXToRight(pos);
	SDL_Point checks[4] = {{left, pos.y + 1}, {left, pos.y - 1}, {right, pos.y + 1}, {right, pos.y - 1}};
	for (int i = 0; i < 4; i++)
	{
		if (AiValidChecker(checks[i]) && map[checks[i].y][checks[i].x].blocked == false)
		{
			t_AiMapUnit **newer = GetReplica(AiIterator::map);
			SetDefaultCharacter(checks[i], newer[character->position.y][character->position.x].character, newer);
			SetDefaultNoCharacter(character->position, newer);
			newer[character->position.y][character->position.x].blocked = false;
			SetAbilityToAction(pos, ability, newer, checks[i]); //slow
			DestroyMap(newer);
		}
	}
}
