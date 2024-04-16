
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
	map[pos.y][pos.x].blocked = true;
	character->position = pos;
}

void AiIterator::SetDefaultNoCharacter(SDL_Point pos, t_AiMapUnit **map)
{
	map[pos.y][pos.x].character = NULL;
	map[pos.y][pos.x].blocked = false;
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

bool AiIterator::RemoveDeadCharacter(t_AiMapUnit **newMap, t_AiCharacter *curr)
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	bool ret = false;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (newMap[i][j].character == NULL)
				continue ;
			if (newMap[i][j].character->alive == false)
			{
				if (newMap[i][j].character == curr)
					ret = true;
				if (newMap[i][j].character->character->cSing == PHANTOM_LION ||
					newMap[i][j].character->character->cSing == TOOLS)
				{
					newMap[i][j].adds.phantom.isIt = false;
					newMap[i][j].adds.phantom.parent = NULL;
					newMap[i][j].adds.phantom.turns = 0;
				}
				delete newMap[i][j].character;
				SetDefaultNoCharacter({j, i}, newMap);
			}
		}
	}
	return (ret);
}

float AiIterator::SendToNextOne(t_AiMapUnit **nmap, t_AiCharacter *character, int movered)
{
	float scr = GetAiScore(nmap, character->character->ally);
	if (depth <= 0)
		return (scr);
	if (RemoveDeadCharacter(nmap, character))
		return (scr);
	AiIterator *next = GetAiIterator();
	next->CalculateMoves(nmap, character, scr, depth - 1, movered);
	float ret = next->GetBestScore();
	ReturnAiIterator(next);
	return (ret);
}

void AiIterator::CalculateMoves(t_AiMapUnit**map, t_AiCharacter *character, float startScore, int depth, int moveMoves)
{
	moveSaves.clear();
	secondLap = false;
	AiIterator::depth = depth;
	AiIterator::character = character;
	AiIterator::map = map;
	AiIterator::startScore = startScore;
	AiIterator::moveMoves = moveMoves;
	action.score = startScore;
	action.same = true;
	action.character = character;
	action.pos = {0, 0};
	if (character == NULL)
		return ;
	action.pos = character->position;
	GetPossibleMoves();
	IterateTheMap();
	ParseMoveSaves();
	IterateTheMap();
}

void AiIterator::IterateTheMap()
{
	if (character == NULL)
		return ;
	if (character->alive == false)
		return ;
	iterationLoop = 0;
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			CheckForAbility({j, i});
			CheckForMove({j, i});
			iterationLoop++;
		}
	}
}

bool AiIterator::InSaves(int iterNum, int type, SDL_Point add)
{
	for (int i = 0; i < moveSaves.size(); i++)
	{
		if (moveSaves[i].iteration == iterNum && moveSaves[i].abilitySign == type &&
			moveSaves[i].secondaryPos.x == add.x && moveSaves[i].secondaryPos.y == add.y)
			return (true);
	}
	return (false);
}

void AiIterator::Destroy()
{
	
}
