
#include "../../../hdr/global.h"
#define ROOM_FOR_MOVE 5

static bool SrotingCompareFuncEnemy(t_MoveIter one, t_MoveIter two)
{
	if (one.abilitySign == two.abilitySign)
	{
		if (one.score < two.score)
			return (true);
		return (false);
	}
	if (one.abilitySign < two.abilitySign)
		return (true);
	return (false);
}

static bool SrotingCompareFuncAlly(t_MoveIter one, t_MoveIter two)
{
	if (one.abilitySign == two.abilitySign)
	{
		if (one.score > two.score)
			return (true);
		return (false);
	}
	if (one.abilitySign < two.abilitySign)
		return (true);
	return (false);
}

void AiIterator::ParseMoveSaves()
{
	secondLap = true;
	if (character->character->ally)
		std::sort(moveSaves.begin(), moveSaves.end(), SrotingCompareFuncAlly);
	else
		std::sort(moveSaves.begin(), moveSaves.end(), SrotingCompareFuncEnemy);
	int counter = 0;
	int currentSign = (-1);
	for (int i = 0; i < moveSaves.size(); i++)
	{
		if (moveSaves[i].abilitySign == currentSign)
		{
			counter++;
			if (counter >= ROOM_FOR_MOVE)
			{
				moveSaves.erase(moveSaves.begin() + i);
				i = (moveSaves.size() == 0) ? 0 : i - 1;
			}
		}
		else
		{
			counter = 0;
			currentSign = moveSaves[i].abilitySign;
		}
	}
}
