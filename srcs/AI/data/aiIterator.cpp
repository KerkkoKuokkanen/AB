
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
				ReturnAiCharacter(newMap[i][j].character);
				SetDefaultNoCharacter({j, i}, newMap);
			}
		}
	}
	return (ret);
}

float AiIterator::SendToNextOne(t_AiMapUnit **nmap, t_AiCharacter *character, int movered, float score)
{
	bool removed = RemoveDeadCharacter(nmap, character);
	float scr = score;
	if (depth <= 0 || removed)
		return (scr);
	next = GetAiIterator();
	next->CalculateMoves(nmap, character, scr, depth - 1, movered);
	float ret = next->GetBestScore();
	ReturnAiIterator(next);
	next = NULL;
	return (ret);
}

void AiIterator::IterateMoveSaves()
{
	for (int i = 0; i < moveSaves.size(); i++)
	{
		currentIterationSave = moveSaves[i];
		if (moveSaves[i].abilitySign == (-1))
			CheckForMove(moveSaves[i].callingPos);
		else
			CheckForAbilitySecondTime(moveSaves[i].callingPos, moveSaves[i].abilitySign);
	}
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
	IterateMoveSaves();
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
			currentIterPosition = {j, i};
			CheckForAbility({j, i});
			CheckForMove({j, i});
		}
	}
}

t_TruthAndScore AiIterator::InSaves(int type, SDL_Point add)
{
	t_TruthAndScore ret = {false, 0.0f};
	if (currentIterationSave.secondaryPos.x == add.x && currentIterationSave.secondaryPos.y == add.y &&
		currentIterationSave.abilitySign == type)
	{
		ret.isIt = true;
		ret.score = currentIterationSave.score;
		return (ret);
	}
	return (ret);
}

void AiIterator::Destroy()
{
	
}
