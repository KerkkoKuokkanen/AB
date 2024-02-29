
#include "../../../hdr/global.h"
#define COUNT_TIME 5
#define ALPHA_TIME 5

static bool NothingToBeDone()
{
	if (gameState.updateObjs.abilities->active == false)
		return (true);
	if (gameState.updateObjs.abilities->inMotion == true)
		return (true);
	if (gameState.updateObjs.abilities->ability == NULL)
		return (true);
	if (gameState.updateObjs.UI->GetActiveCharacter() == NULL)
		return (true);
	return (false);
}

void HitChanceBubble::Deleting()
{
	if (bubble != NULL)
		delete bubble;
	bubble = NULL;
	counter = 0;
}

void HitChanceBubble::Update(Character *hovered)
{
	if (NothingToBeDone() || hovered == NULL)
	{
		Deleting();
		return ;
	}
	int current = gameState.updateObjs.abilities->ability->type;
	if (currAbility != current)
	{
		Deleting();
		counter = 0;
		currAbility = current;
		return ;
	}
	counter = (counter > 30) ? counter : counter++;
	if (counter == COUNT_TIME)
		
}
