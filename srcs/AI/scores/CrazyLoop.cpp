
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

static int CharacterDistanceToPosition(SDL_Point pos, t_AiCharacter *target, bool staticSearch)
{
	SDL_Point targ = target->position;
	if (staticSearch)
	{
		int dist = moveMaps.staticMoves[targ.y][targ.x].map[pos.y][pos.x];
		return (dist);
	}
	int dist = moveMaps.abilities[targ.y][targ.x].map[pos.y][pos.x];
	return (dist);
}

float CrazyLoopScore(t_AiMapUnit **map, std::vector<t_AiCharacter*> &charQ)
{
	OrderTheCharQ(charQ);
	ReturnMapPositionDistances({0, 0}, map, charQ[0], 2, true, 0, 0, charQ);
	DestroyMap(map);
	return (0.0f);
}
