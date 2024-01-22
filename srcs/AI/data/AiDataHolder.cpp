
#include "../../../hdr/global.h"

static void CopyStatusesFromTheCharacter(t_AiCharacter *aiChar, t_AiCharacter *character)
{
	for (int i = 0; i < character->statuses.bleed.size(); i++)
		aiChar->statuses.bleed.push_back(character->statuses.bleed[i]);
	for (int i = 0; i < character->statuses.buffs.size(); i++)
		aiChar->statuses.buffs.push_back(character->statuses.buffs[i]);
	for (int i = 0; i < character->statuses.burns.size(); i++)
		aiChar->statuses.burns.push_back(character->statuses.burns[i]);
	for (int i = 0; i < character->statuses.deBuffs.size(); i++)
		aiChar->statuses.deBuffs.push_back(character->statuses.deBuffs[i]);
	for (int i = 0; i < character->statuses.poison.size(); i++)
		aiChar->statuses.poison.push_back(character->statuses.poison[i]);
	for (int i = 0; i < character->statuses.toxicBlade.size(); i++)
		aiChar->statuses.toxicBlade.push_back(character->statuses.toxicBlade[i]);
	aiChar->statuses.hosting = character->statuses.hosting;
	aiChar->statuses.hosted = character->statuses.hosted;
	aiChar->statuses.controlZone = character->statuses.controlZone;
	aiChar->statuses.stun = character->statuses.stun;
	aiChar->statuses.slowed = character->statuses.slowed;
}

static t_AiCharacter *SetTheCharacter(t_AiCharacter *character)
{
	if (character == NULL)
		return (NULL);
	t_AiCharacter *used = new t_AiCharacter;
	used = new t_AiCharacter;
	used->alive = character->alive;
	used->armor = character->armor;
	used->health = character->health;
	used->fatigue = character->fatigue;
	used->moves = character->moves;
	used->character = character->character;
	used->position = character->position;
	CopyStatusesFromTheCharacter(used, character);
	return (used);
}

t_AiMapUnit **GetReplica(t_AiMapUnit **map)
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	t_AiMapUnit **ret = (t_AiMapUnit**)malloc(sizeof(t_AiMapUnit*) * h);
	for (int i = 0; i < h; i++)
	{
		ret[i] = (t_AiMapUnit*)malloc(sizeof(t_AiMapUnit) * w);
		for (int j = 0; j < w; j++)
		{
			ret[i][j].blocked = map[i][j].blocked;
			ret[i][j].height = map[i][j].height;
			ret[i][j].obj = map[i][j].obj;
			ret[i][j].adds = map[i][j].adds;
			ret[i][j].movable = TOOL_MAP_SIGN;
			ret[i][j].character = SetTheCharacter(map[i][j].character);
		}
	}
	return (ret);
}

void DestroyMap(t_AiMapUnit **map)
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (map[i][j].character != NULL)
				delete (map[i][j].character);
		}
	}
	for (int i = 0; i < h; i++)
		free(map[i]);
	free(map);
}
