
#include "../../../hdr/global.h"

void AiIterator::GetPossibleMoves()
{
	if (character.alive == false)
		return ;
	GetAiMapMoves(&character, map);
}

void AiIterator::SetDefaultCharacter(SDL_Point pos, t_AiCharacter *character, t_AiMapUnit **map)
{
	map[pos.y][pos.x].character.alive = character->alive;
	map[pos.y][pos.x].character.armor = character->armor;
	map[pos.y][pos.x].character.health = character->health;
	map[pos.y][pos.x].character.fatigue = character->fatigue;
	map[pos.y][pos.x].character.moves = character->moves;
	map[pos.y][pos.x].character.character = character->character;
	map[pos.y][pos.x].character.position = pos;
	map[pos.y][pos.x].character.statuses = character->statuses;
}

void AiIterator::SetDefaultNoCharacter(SDL_Point pos, t_AiMapUnit **map)
{
	map[pos.y][pos.x].character.character = NULL;
	map[pos.y][pos.x].character.alive = false;
	map[pos.y][pos.x].character.armor = 0;
	map[pos.y][pos.x].character.health = 0;
	map[pos.y][pos.x].character.fatigue = 0;
	map[pos.y][pos.x].character.moves = 0;
	map[pos.y][pos.x].character.position = {0, 0};
	bzero(&map[pos.y][pos.x].character.statuses, sizeof(t_StatusEffects));
}

t_AiCharacter *AiIterator::GetCharInMap()
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (map[i][j].character.character == character.character)
				return (&map[i][j].character);
		}
	}
	return (NULL);
}

void AiIterator::TurnStartActions()
{
	t_AiCharacter *character = GetCharInMap();
	TurnStartMapEffects();
	TurnStartCharacterChecks(character);
}

void AiIterator::DoThePassAction(int fromPass)
{
	if (fromPass == 0)
		return ;
	if (fromPass == 1)
	{
		TurnStartActions();
		return ;
	}
	RoundStartMapChecks();
	TurnStartActions();
}
//sprite making
void AiIterator::TurnEndActions()
{	///continue from here. Crash here because of the new shit
	t_AiCharacter *character = GetCharInMap();
	TurnEndChecks(character);
	t_AiCharacter *next = NULL;
	t_SomeRetShit ret = GetNextCharacter(character, next, map);
	if (ret.character == NULL)
		return ;
	t_AiCharacter &send = map[ret.character->position.y][ret.character->position.x].character;
	float score = SendToNextOne(map, send, ret.type);
	if (character->character->ally)
	{
		if (score > action.score)
		{
			action.same = true;
			action.score = score;
		}
		return ;
	}
	if (score < action.score)
	{
		action.same = true;
		action.score = score;
	}
}

void AiIterator::RemoveDeadCharacter(t_AiMapUnit **newMap)
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (newMap[i][j].character.alive == false)
				SetDefaultNoCharacter({j, i}, newMap);
		}
	}
}

float AiIterator::SendToNextOne(t_AiMapUnit **nmap, t_AiCharacter &character, int fromPass)
{
	float scr = GetAiScore(nmap, character.character->ally);
	if (depth <= 0)
		return (scr);
	RemoveDeadCharacter(nmap);
	AiIterator *next = GetAiIterator();
	next->CalculateMoves(nmap, character, scr, depth - 1, fromPass);
	float ret = next->GetBestScore();
	return (ret);
}

void AiIterator::CalculateMoves(t_AiMapUnit**map, t_AiCharacter &character, float startScore, int depth, int fromPass)
{
	AiIterator::depth = depth;
	AiIterator::character = character;
	AiIterator::map = map;
	AiIterator::startScore = startScore;
	AiIterator::character.position = GetCharInMap()->position;
	action.score = startScore;
	action.same = true;
	action.character = &character;
	action.pos = character.position;
	DoThePassAction(fromPass);
	GetPossibleMoves();
	IterateTheMap();
	TurnEndActions();
}

void AiIterator::IterateTheMap()
{
	if (character.alive == false)
		return ;
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			CheckForAbility({j, i});
			CheckForMove({j, i});
		}
	}
}

void AiIterator::Destroy()
{
	
}
