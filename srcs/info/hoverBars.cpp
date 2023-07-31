
#include "../../hdr/global.h"
#define HOW_MUCH_THE_BAR_NEEDS_TO_BE_ON_TOP -220
#define THE_HOVER_BAR_WIDTH 3200

HoverBars::HoverBars()
{
	SDL_Rect dest1 = {0, 0, THE_HOVER_BAR_WIDTH, 500};
	SDL_Rect dest2 = {0, HOW_MUCH_THE_BAR_NEEDS_TO_BE_ON_TOP, THE_HOVER_BAR_WIDTH, 500};
	health = new Bar(dest1, false, false);
	armor = new Bar(dest2, false, false);
	health->ChangeToSmallBar();
	armor->ChangeToSmallBar();
	armor->SetColor(201, 14, 14);
	health->SetColor(101, 97, 135);
}

SDL_Point HoverBars::GetHealthPosition()
{
	Vector topMid((float)(target->sprite->dest.x + target->topMid.x), (float)(target->sprite->dest.y + target->topMid.y));
	topMid.y -= 1000.0f;
	int diff = THE_HOVER_BAR_WIDTH / 2;
	topMid.x -= (float)diff;
	SDL_Point place = {rounding(topMid.x), rounding(topMid.y)};
	return (place);
}

void HoverBars::PlaceBars(SDL_Point place)
{
	health->Position(place);
	place.y -= HOW_MUCH_THE_BAR_NEEDS_TO_BE_ON_TOP;
	armor->Position(place);
}

void HoverBars::CreateStatuses(SDL_Point place)
{
	if (statuses != NULL)
		delete statuses;
	Vector pos((float)place.x, (float)(place.y - HOW_MUCH_THE_BAR_NEEDS_TO_BE_ON_TOP - 740.0f));
	statuses = new Statuses(target, 640, 310, false);
	statuses->Postion(pos);
}

void HoverBars::ManageStatuses()
{
	if (target == NULL)
		return ;
	statuses->Update();
}

void HoverBars::Update(Character *target)
{
	if (target == NULL || target->killed || gameState.updateObjs.abilities->active || target->damaged
		|| gameState.updateObjs.turnOrder->turnChange || gameState.updateObjs.turnOrder->turnStartActive ||
		gameState.modes.filterMode == 2)
	{
		HoverBars::target = NULL;
		health->Deactivate();
		armor->Deactivate();
		if (statuses != NULL)
			delete statuses;
		statuses = NULL;
		return ;
	}
	health->Activate();
	armor->Activate();
	if (HoverBars::target != target)
	{
		HoverBars::target = target;
		SDL_Point place = GetHealthPosition();
		PlaceBars(place);
		CreateStatuses(place);
	}
	ManageStatuses();
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
