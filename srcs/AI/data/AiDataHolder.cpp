
#include "../../../hdr/global.h"
#define FREE_CHARS_SIZE 80
#define FREE_MAPS_SIZE 50
#define ITERATOR_SIZE 500

static AiObjHolder objHolder;

void InitObjHolder()
{
	objHolder.Init();
}

void ClearObjHolder()
{
	objHolder.Clear();
}

static void ResetCharacter(t_AiCharacter *character)
{
	character->statuses.bleed.clear();
	character->statuses.buffs.clear();
	character->statuses.burns.clear();
	character->statuses.deBuffs.clear();
	character->statuses.poison.clear();
	character->statuses.toxicBlade.clear();
}

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
	aiChar->statuses.frenzy = character->statuses.frenzy;
}

static t_AiCharacter *SetTheCharacter(t_AiCharacter *character)
{
	if (character == NULL)
		return (NULL);
	t_AiCharacter *used = objHolder.GetCharacter();
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

t_AiCharacter *GetReplicaAiCharacter(t_AiCharacter *copied)
{
	t_AiCharacter *ret = SetTheCharacter(copied);
	return (ret);
}

t_AiMapUnit **GetMapFromHolder()
{
	t_AiMapUnit **ret = objHolder.GetMap();
	return (ret);
}

void AiObjHolder::ReturnCharacter(t_AiCharacter *character)
{
	charsInUse.erase(character);
	character->alive = false;
	ResetCharacter(character);
	freeCharacters.push_back(character);
}

void ReturnAiCharacter(t_AiCharacter *aiCharacter)
{
	objHolder.ReturnCharacter(aiCharacter);
}

t_AiCharacter *GetAiCharacterFromHolder()
{
	t_AiCharacter *ret = objHolder.GetCharacter();
	return (ret);
}

AiIterator *GetAiIterator()
{
	AiIterator *ret = objHolder.GetIterator();
	return (ret);
}

void ReturnAiIterator(AiIterator *iterator)
{
	objHolder.ReturnAiIterator(iterator);
}

t_AiMapUnit **GetReplica(t_AiMapUnit **map)
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	t_AiMapUnit **ret = objHolder.GetMap();
	for (int i = 0; i < h; i++)
	{
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
	objHolder.ReturnMap(map);
}

static t_AiMapUnit **GetTheMapForHolder()
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	t_AiMapUnit **map = (t_AiMapUnit**)malloc(sizeof(t_AiMapUnit*) * h);
	for (int i = 0; i < h; i++)
	{
		map[i] = (t_AiMapUnit*)malloc(sizeof(t_AiMapUnit) * w);
		bzero(map[i], sizeof(t_AiMapUnit) * w);
	}
	return (map);
}

void AiObjHolder::ReturnMap(t_AiMapUnit **map)
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (map[i][j].character != NULL)
			{
				ResetCharacter(map[i][j].character);
				charsInUse.erase(map[i][j].character);
				freeCharacters.push_back(map[i][j].character);
				map[i][j].character = NULL;
			}
		}
	}
	mapsInUse.erase(map);
	freeMaps.push_back(map);
}

t_AiCharacter *AiObjHolder::GetCharacter()
{
	if (freeCharacters.size() > 0)
	{
		t_AiCharacter *ret = freeCharacters.back();
		freeCharacters.pop_back();
		charsInUse.insert(ret);
		return (ret);
	}
	t_AiCharacter *ret = new t_AiCharacter;
	bzero(ret, sizeof(t_AiCharacter));
	charsInUse.insert(ret);
	return (ret);
}

t_AiMapUnit **AiObjHolder::GetMap()
{
	if (freeMaps.size() > 0)
	{
		t_AiMapUnit **ret = freeMaps.back();
		mapsInUse.insert(ret);
		freeMaps.pop_back();
		return (ret);
	}
	t_AiMapUnit **ret = GetTheMap();
	mapsInUse.insert(ret);
	return (ret);
}

void AiObjHolder::ReturnAiIterator(AiIterator *itertor)
{
	iteratorsInUse.erase(itertor);
	freeIterators.push_back(itertor);
}

AiIterator *AiObjHolder::GetIterator()
{
	if (freeIterators.size() > 0)
	{
		AiIterator *ret = freeIterators.back();
		freeIterators.pop_back();
		iteratorsInUse.insert(ret);
		return (ret);
	}
	AiIterator *ret = new AiIterator;
	iteratorsInUse.insert(ret);
	return (ret);
}

void AiObjHolder::Init()
{
	for (int i = 0; i < FREE_MAPS_SIZE; i++)
	{
		t_AiMapUnit **map = GetTheMapForHolder();
		freeMaps.push_back(map);
	}
	for (int i = 0; i < FREE_CHARS_SIZE; i++)
	{
		t_AiCharacter *character = new t_AiCharacter;
		bzero(character, sizeof(t_AiCharacter));
		freeCharacters.push_back(character);
	}
	for (int i = 0; i < ITERATOR_SIZE; i++)
	{
		AiIterator *iter = new AiIterator;
		freeIterators.push_back(iter);
	}
}

static void EraseMap(t_AiMapUnit **map)
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
		free(map[i]);
	free(map);
}

void AiObjHolder::Clear()
{
	for (int i = 0; i < freeMaps.size(); i++)
		EraseMap(freeMaps[i]);
	for (int i = 0; i < freeIterators.size(); i++)
		delete freeIterators[i];
	for (int i = 0; i < freeCharacters.size(); i++)
		delete freeCharacters[i];
	for (t_AiMapUnit **element : mapsInUse)
		EraseMap(element);
	for (t_AiCharacter *element : charsInUse)
		delete element;
	for (AiIterator *element : iteratorsInUse)
		delete element;
	freeMaps.clear();
	freeIterators.clear();
	freeCharacters.clear();
	mapsInUse.clear();
	charsInUse.clear();
	iteratorsInUse.clear();
}
