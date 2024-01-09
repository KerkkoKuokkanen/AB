
#include "../../../hdr/global.h"

t_TargetingType GetAbilityTargetingType(t_Ability *ability)
{
	t_TargetingType ret = {0, 0, false, false};
	switch (ability->type)
	{
		case DAGGER_THROW:
			ret = {ability->range, SelectorTypesForAi::SELECTOR, true, false};
			break ;
		case DAGGER_SLASH:
			ret = {ability->range, SelectorTypesForAi::SELECTOR, true, true};
			break ;
		case SMOKE_BOMB:
			ret = {ability->range, SelectorTypesForAi::TILE_SELECTOR, true, false};
			break ;
	}
	return (ret);
}
