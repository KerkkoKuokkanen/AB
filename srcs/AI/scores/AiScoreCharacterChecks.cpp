
#include "../../../hdr/global.h"

static bool CompareFunction(SDL_Point one, SDL_Point two)
{
	return (one.x < two.x);
}

// (figure out the best way to check the relevant positions)
// -> position scores for character in terms of abilites and their range
// -> position score could for example have three parts like: offence, defence and utility
// (maybe try abilities in the current position MAYBE)
// -> move to different positions in terms of the score
//    if character cant reach these positions move to positions close to the best positions
// -> try abilities in the different positions
// -> final score is health scores and position scores combined

std::vector<SDL_Point> GetCharacterEffectiveDistances(t_AiCharacter *character)
{
	std::vector<SDL_Point> ranges = {};
	for (int i = 0; i < character->character->abilities.size(); i++)
	{
		int range = character->character->abilities[i].range;
		bool melee = character->character->abilities[i].melee;
		ranges.push_back({range, (melee == true) ? 1 : 0});
	}
	std::sort(ranges.begin(), ranges.end(), CompareFunction);
	return (ranges);
}
