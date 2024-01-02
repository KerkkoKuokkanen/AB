
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
	passTested = false;
	GetPossibleMoves();
}

void AiIterator::Destroy()
{

}
