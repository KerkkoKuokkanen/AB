
#include "../../../hdr/global.h"
#define ACTIVATION_TRESHOLD 36
#define ALPHA_MAXED 10

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
	{
		bubble = new TextBubble({0, 0});
		bubble->SetMouseFollow({0, 0});
		bubble->SetFollowCorner(2);
		CreateBubble();
	}
	bubble->Update();
	int count = counter - ACTIVATION_TRESHOLD;
	float unit = 255.0f / ALPHA_MAXED;
	int alpha = rounding(unit * (float)count);
	if (alpha > 255)
	{
		bubble->ClearAlphaMod();
		return ;
	}
	bubble->SetAlphaMod(alpha);
}

void UiTextUpdater::Update(int ability)
{
	if (ability <= 0)
	{
		if (bubble != NULL)
			delete bubble;
		bubble = NULL;
		counter = 0;
		return ;
	}
	if (ability == currentAbility)
		counter++;
	else
	{
		currentAbility = ability;
		counter = 0;
	}
	UpdateBubble();
}
