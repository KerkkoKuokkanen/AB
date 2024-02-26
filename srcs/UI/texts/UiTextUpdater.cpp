
#include "../../../hdr/global.h"
#define ACTIVATION_TRESHOLD 28
#define ALPHA_MAXED 55

void UiTextUpdater::UpdateBubble()
{
	if (counter < ACTIVATION_TRESHOLD)
	{
		if (bubble != NULL)
			delete bubble;
		bubble = NULL;
		return ;
	}
	if (bubble == NULL)
		CreateBubble();
}

void UiTextUpdater::Update(int ability)
{
	if (ability <= 0)
		return ;
	if (ability == currentAbility)
		counter++;
	else
	{
		currentAbility = ability;
		counter = 0;
	}
	UpdateBubble();
}
