
#include "../../../hdr/global.h"

static bool CheckCoordForBox(SDL_Point pos)
{
	if (!CheckIfValidPosition(pos))
		return (false);
	t_GMU *used = &gameState.battle.ground->map[pos.y][pos.x];
	if (used->additional.object == NULL)
		return (false);
	if (used->additional.type == AdditionalObjects::TOOLBOX)
		return (true);
	return (false);
}

bool CheckIfNextToToolBox(SDL_Point pos)
{
	int left = getXToLeft(pos);
	int right = getXToRight(pos);
	if (CheckCoordForBox({left, pos.y - 1}))
		return (true);
	if (CheckCoordForBox({left, pos.y + 1}))
		return (true);
	if (CheckCoordForBox({right, pos.y - 1}))
		return (true);
	if (CheckCoordForBox({right, pos.y + 1}))
		return (true);
	return (false);
}

std::vector<Character*> GetPositionControllers(SDL_Point pos)
{
	int left = getXToLeft(pos);
	int right = getXToRight(pos);
}
