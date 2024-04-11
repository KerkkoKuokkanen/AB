
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

static int GetCharactersDistToPosition(t_AiMapUnit **map, SDL_Point position, t_AiCharacter *character)
{
	SDL_Point start = character->position;
	int dist = RangeBetweenPositions(map, start, position);
	return (dist);
}

static bool PositionHasTargetsInRange(int range, SDL_Point position, std::vector<t_AiCharacter*> &charQ, int targetType, bool staticDist, bool ally)
{
	for (int i = 0; i < charQ.size(); i++)
	{
		if (targetType == 0 && charQ[i]->character->ally == ally)
			continue ;
		if (targetType == 1 && charQ[i]->character->ally != ally)
			continue ;
		SDL_Point check = charQ[i]->position;
		int dist = 0;
		if (!staticDist)
			dist = moveMaps.abilities[position.y][position.x].map[check.y][check.x];
		else
			dist = moveMaps.staticMoves[position.y][position.x].map[check.y][check.x];
		if (dist == 0)
			continue ;
		if (dist <= range)
			return (true);
	}
	return (false);
}

std::vector<t_PointDist> FindPositionsWithDistance(t_AiMapUnit **map, t_AiCharacter *character, int distance, bool staticDist, int targetType, int saveCount, std::vector<t_AiCharacter*> &charQ)
{
	int w = gameState.battle.ground->map[0].size();
	int h = gameState.battle.ground->map.size();
	SDL_Point pos = character->position;
	bool ally = character->character->ally;
	std::vector<t_PointDist> ret = {};
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (!PositionHasTargetsInRange(distance, {j, i}, charQ, targetType, staticDist, ally))
				continue ;
			t_PointDist add = {{j, i}, 0, 0};
			add.distance = GetCharactersDistToPosition(map, {j, i}, character);
			ret.push_back(add);
		}
	}
	return (ret);
}

float CrazyLoopScore(t_AiMapUnit **map, std::vector<t_AiCharacter*> &charQ)
{
	OrderTheCharQ(charQ);
	std::vector<t_PointDist> ret = FindPositionsWithDistance(map, charQ[0], 2, true, 0, 0, charQ);
	DestroyMap(map);
	return (0.0f);
}
