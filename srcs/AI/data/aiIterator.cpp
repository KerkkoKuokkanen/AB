
#include "../../../hdr/global.h"

void AiIterator::GetPossibleMoves()
{
	GetAiMapMoves(&character, map);
}

void AiIterator::CalculateMoves(t_AiMapUnit**map, t_AiCharacter character, float startScore, int depth)
{
	AiIterator::depth = depth - 1;
	AiIterator::character = character;
	AiIterator::map = map;
	AiIterator::startScore = startScore;
	action = {startScore, true};
	GetPossibleMoves();
	IterateTheMap();
}

void AiIterator::IterateTheMap()
{
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
