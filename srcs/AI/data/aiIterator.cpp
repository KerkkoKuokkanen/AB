
#include "../../../hdr/global.h"

void AiIterator::GetPossibleMoves()
{
	if (character == NULL)
		return ;
	if (character->alive == false)
		return ;
	GetAiMapMoves(character, map);
}

void AiIterator::SetDefaultCharacter(SDL_Point pos, t_AiCharacter *character, t_AiMapUnit **map)
{
	map[pos.y][pos.x].character = character;
	character->position = pos;
}

void AiIterator::SetDefaultNoCharacter(SDL_Point pos, t_AiMapUnit **map)
{
	map[pos.y][pos.x].character = NULL;
}

t_AiCharacter *AiIterator::GetCharInMap()
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (map[i][j].character == character)
				return (map[i][j].character);
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
	if (character == NULL)
		return ;
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

void AiIterator::TurnEndActions()
{
	TurnEndChecks(character);
	t_AiCharacter *next = NULL;
	t_SomeRetShit ret = GetNextCharacter(character, next, map);
	if (ret.character == NULL)
		return ;
	float score = SendToNextOne(map, map[ret.character->position.y][ret.character->position.x].character, ret.type);
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
			if (newMap[i][j].character == NULL)
				continue ;
			if (newMap[i][j].character->alive == false)
			{
				delete newMap[i][j].character;
				SetDefaultNoCharacter({j, i}, newMap);
			}
		}
	}
}

float AiIterator::SendToNextOne(t_AiMapUnit **nmap, t_AiCharacter *character, int fromPass)
{
	float scr = GetAiScore(nmap, character->character->ally);
	if (depth <= 0)
		return (scr);
	RemoveDeadCharacter(nmap); //I need to check that the character that we send next is not null
	AiIterator *next = GetAiIterator();
	next->CalculateMoves(nmap, character, scr, depth - 1, fromPass);
	float ret = next->GetBestScore();
	return (ret);
}

void AiIterator::CalculateMoves(t_AiMapUnit**map, t_AiCharacter *character, float startScore, int depth, int fromPass)
{
	AiIterator::depth = depth;
	AiIterator::character = character;
	AiIterator::map = map;
	AiIterator::startScore = startScore;
	action.score = startScore;
	action.same = true;
	action.character = character;
	if (character == NULL)
		action.pos = {0, 0};
	else
		action.pos = character->position;
	if (character == NULL)
		return ;
	DoThePassAction(fromPass);
	GetPossibleMoves();
	IterateTheMap();
	TurnEndActions();
}

void AiIterator::IterateTheMap()
{
	if (character == NULL)
		return ;
	if (character->alive == false)
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
