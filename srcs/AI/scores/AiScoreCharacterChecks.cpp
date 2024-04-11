
#include "../../../hdr/global.h"

static bool CompareFunction(SDL_Point one, SDL_Point two)
{
	return (one.x < two.x);
}

std::vector<SDL_Point> GetCharacterEffectiveDistances(t_AiCharacter *character)
{
	std::vector<SDL_Point> ranges = {};
	for (int i = 0; i < character->character->abilities.size(); i++)
	{
		int range = character->character->abilities[i].range;
		int index = i;
		ranges.push_back({range, index});
	}
	std::sort(ranges.begin(), ranges.end(), CompareFunction);
	return (ranges);
}
