
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
	action = {startScore};
	GetPossibleMoves();
	CalculateAbilityScores();
}

void AiIterator::CheckDefaultAbilities()
{
	for (int i = 0; i < character.character->abilities.size(); i++)
		SendToTargeting(&character.character->abilities[i]);
}

void AiIterator::CalculateAbilityScores()
{
	CheckDefaultAbilities();
}

void AiIterator::Destroy()
{
	
}
