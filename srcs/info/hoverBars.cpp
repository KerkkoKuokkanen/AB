
#include "../../hdr/global.h"
#define HOW_MUCH_THE_BAR_NEEDS_TO_BE_ON_TOP -150
#define THE_HOVER_BAR_WIDTH 3200

HoverBars::HoverBars()
{
	SDL_Rect dest1 = {0, 0, THE_HOVER_BAR_WIDTH, 200};
	SDL_Rect dest2 = {0, HOW_MUCH_THE_BAR_NEEDS_TO_BE_ON_TOP, THE_HOVER_BAR_WIDTH, 200};
	health = new Bar(dest1, false, false);
	armor = new Bar(dest2, false, false);
	armor->SetColor(201, 14, 14);
	health->SetColor(125, 125, 125);
}

void HoverBars::PlaceBars()
{
	Vector topMid = GetCharacterTopMid(target);
	topMid.y -= 700.0f;
	int diff = THE_HOVER_BAR_WIDTH / 2;
	topMid.x -= (float)diff;
	SDL_Point place = {rounding(topMid.x), rounding(topMid.y)};
	health->Position(place);
	place.y -= HOW_MUCH_THE_BAR_NEEDS_TO_BE_ON_TOP;
	armor->Position(place);
}

void HoverBars::Update(Character *target)
{
	if (target == NULL || target->killed)
	{
		HoverBars::target = target;
		health->Deactivate();
		armor->Deactivate();
		return ;
	}
	health->Activate();
	armor->Activate();
	if (HoverBars::target != target)
	{
		HoverBars::target = target;
		PlaceBars();
	}
	health->Update(target, false);
	armor->Update(target, true);
}

void HoverBars::Destroy()
{
	if (health != NULL)
		delete health;
	if (armor != NULL)
		delete armor;
	health = NULL;
	armor = NULL;
}
