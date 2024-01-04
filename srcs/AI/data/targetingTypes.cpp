
#include "../../../hdr/global.h"

t_TargetingType GetAbilityTargetingType(t_Ability *ability)
{
	t_TargetingType ret = {{0, 0}};
	switch (ability->type)
	{
		case DAGGER_THROW:
			ret.rangeAndType = {ability->range, SelectorTypesForAi::SELECTOR};
			break ;
		case DAGGER_SLASH:
			ret.rangeAndType = {ability->range, SelectorTypesForAi::SELECTOR};
			break ;
		case SMOKE_BOMB:
			ret.rangeAndType = {ability->range, SelectorTypesForAi::TILE_SELECTOR};
			break ;
	}
	return (ret);
}
