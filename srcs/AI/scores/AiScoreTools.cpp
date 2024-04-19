
#include "../../../hdr/global.h"

static bool compareObjects(const t_AiCharacter *obj1, const t_AiCharacter *obj2)
{
	if (obj1->character->stats.speed == obj2->character->stats.speed)
	{
		if (obj1->character->ally)
			return (true);
	}
	return (obj1->character->stats.speed > obj2->character->stats.speed);
}

void RemoveTheDead(t_AiMapUnit **map, std::vector<t_AiCharacter*> &charQ)
{
	for (int i = 0; i < charQ.size(); i++)
	{
		t_AiCharacter *charac = charQ[i];
		if (charac->alive == false)
		{
			SDL_Point pos = charac->position;
			map[pos.y][pos.x].character = NULL;
			map[pos.y][pos.x].blocked = false;
			charQ.erase(charQ.begin() + i);
			i = (charQ.size() == 0) ? 0 : i - 1;
		}
	}
}

void OrderTheCharQ(std::vector<t_AiCharacter*> &charQ) //This function crashes
{
	int iter = 0;
	int size = charQ.size();
	std::sort(charQ.begin(), charQ.end(), compareObjects);
	while (true)
	{
		t_AiCharacter *curr = charQ.front();
		if (curr->character->turn)
			break ;
		charQ.erase(charQ.begin());
		charQ.push_back(curr);
		iter++;
		if (iter == size)
			break ;
	}
}

static SDL_Point GetNextSmallest(SDL_Point pos, SDL_Point start, t_AiMapUnit **map)
{
	int distance = moveMaps.abilities[start.y][start.x].map[pos.y][pos.x];
	if (distance <= 0)
		return (pos);
	int left = AiGetXToLeft(pos);
	int right = AiGetXToRight(pos);
	SDL_Point positions[4] = {{left, pos.y - 1}, {left, pos.y + 1}, {right, pos.y - 1}, {right, pos.y + 1}};
	SDL_Point retPos = {-1, -1};
	bool currentlyBlocked = true;
	for (int i = 0; i < 4; i++)
	{
		if (!AiValidPos(positions[i]))
			continue ;
		int found = moveMaps.abilities[start.y][start.x].map[positions[i].y][positions[i].x];
		if (found == TOOL_MAP_SIGN)
			continue ;
		if (found <= distance)
		{
			if (found == distance && !map[positions[i].y][positions[i].x].blocked && currentlyBlocked)
			{
				currentlyBlocked = false;
				distance = found;
				retPos = {positions[i].x, positions[i].y};
			}
			else
			{
				currentlyBlocked = map[positions[i].y][positions[i].x].blocked;
				distance = found;
				retPos = {positions[i].x, positions[i].y};
			}
		}
	}
	return (retPos);
}

static int AiIsControlledAmount(SDL_Point pos, bool ally, t_AiMapUnit **map)
{
	int left = AiGetXToLeft(pos);
	int right = AiGetXToRight(pos);
	SDL_Point positions[4] = {{left, pos.y + 1}, {left, pos.y - 1}, {right, pos.y + 1}, {right, pos.y - 1}};
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (!AiValidPos(positions[i]))
			continue ;
		t_AiCharacter *used = map[positions[i].y][positions[i].x].character;
		if (used == NULL)
			continue ;
		if (AiCheckSmoked(positions[i], map))
			continue ;
		if (used->character->ally != ally)
			count++;
	}
	return (count);
}

int RangeBetweenPositionsWithControls(t_AiMapUnit **map ,SDL_Point start, SDL_Point end, bool ally)
{
	int distance = moveMaps.abilities[start.y][start.x].map[end.y][end.x];
	int current = distance;
	SDL_Point next = end;
	while (current != 0)
	{
		next = GetNextSmallest(next, start, map);
		if (next.x == (-1))
			return (-1);
		current = moveMaps.abilities[start.y][start.x].map[next.y][next.x];
		if (current <= 0)
			break ;
		int controlAmount = AiIsControlledAmount(next, ally, map);
		if (map[next.y][next.x].blocked)
			distance += 4;
		distance += 2 * controlAmount;
	}
	return (distance);
}

int RangeBetweenPositions(t_AiMapUnit **map ,SDL_Point start, SDL_Point end)
{
	int distance = moveMaps.abilities[start.y][start.x].map[end.y][end.x];
	int current = distance;
	SDL_Point next = end;
	while (current != 0)
	{
		next = GetNextSmallest(next, start, map);
		if (next.x == (-1))
			return (-1);
		current = moveMaps.abilities[start.y][start.x].map[next.y][next.x];
		if (current <= 0)
			break ;
		if (map[next.y][next.x].blocked)
			distance += 4;
	}
	return (distance);
}

static float AiGetOppChance(t_AiCharacter *character, t_AiMapUnit **map)
{
	int y = character->position.y;
	int left = AiGetXToLeft(character->position);
	int right = AiGetXToRight(character->position);
	float chanceForHit = 1.0f;
	SDL_Point positions[4] = {{left, y - 1}, {left, y + 1}, {right, y - 1}, {right, y + 1}};
	bool ally = character->character->ally;
	for (int i = 0; i < 4; i++)
	{
		if (!AiValidPos(positions[i]))
			continue ;
		if (map[positions[i].y][positions[i].x].adds.smoke.isIt)
			continue ;
		t_AiCharacter *used = map[positions[i].y][positions[i].x].character;
		if (used == NULL || used->character->ally == ally)
			continue ;
		int chance = AiGetChance(used, character, NULL, map);
		float chancer = (float)chance / 100.0f;
		chanceForHit *= (1.0f - chancer);
	}
	chanceForHit = 1.0f - chanceForHit;
	return (chanceForHit);
}

static bool NoDamageMelee(t_AiCharacter *character)
{
	for (int i = 0; i < character->character->abilities.size(); i++)
	{
		t_Ability *used = &character->character->abilities[i];
		if (used->melee == false && used->damage > 0)
			return (false);
	}
	return (true);
}

bool NoPointInMovingControlChecks(t_AiCharacter *character, t_AiMapUnit **map, std::vector<t_AiCharacter*> &charQ)
{
	if (NoDamageMelee(character))
		return (false);
	if (AiGetOppChance(character, map) > 0.51f)
		return (true);
	return (false);
}
