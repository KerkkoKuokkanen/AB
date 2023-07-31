
#include "../../hdr/global.h"
#define HOW_MUCH_THE_BAR_NEEDS_TO_BE_ON_TOP -220
#define THE_HOVER_BAR_WIDTH 3200

void FilterModeBars::PostionBars(Character *target, t_FilterBars &bars)
{
	Vector topMid((float)(target->sprite->dest.x + target->topMid.x), (float)(target->sprite->dest.y + target->topMid.y));
	topMid.y -= 1000.0f;
	int diff = THE_HOVER_BAR_WIDTH / 2;
	topMid.x -= (float)diff;
	SDL_Point place = {rounding(topMid.x), rounding(topMid.y)};
	bars.health->Position(place);
	place.y = place.y - HOW_MUCH_THE_BAR_NEEDS_TO_BE_ON_TOP;
	bars.armor->Position(place);
	Vector pos((float)place.x, (float)(place.y - 740.0f));
	bars.status->Postion(pos);
}

FilterModeBars::FilterModeBars()
{
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		t_FilterBars add;
		Character *target = gameState.battle.ground->characters[i].character;
		SDL_Rect dest = {0, 0, THE_HOVER_BAR_WIDTH, 500};
		add.health = new Bar(dest, false, false);
		add.armor = new Bar(dest, false, false);
		add.health->ChangeToSmallBar();
		add.armor->ChangeToSmallBar();
		add.armor->SetColor(201, 14, 14);
		add.health->SetColor(101, 97, 135);
		add.status = new Statuses(target, 640, 310, false);
		PostionBars(target, add);
		add.armor->Update(target, true);
		add.health->Update(target, false);
		add.status->Update();
		bars.push_back(add);
	}
}

void FilterModeBars::Update()
{
	for (int i = 0; i < bars.size(); i++)
	{
		bars[i].armor->Update(bars[i].target, true);
		bars[i].health->Update(bars[i].target, false);
		bars[i].status->Update();
	}
}

void FilterModeBars::Destroy()
{
	for (int i = 0; i < bars.size(); i++)
	{
		delete bars[i].armor;
		delete bars[i].health;
		delete bars[i].status;
	}
	bars.clear();
}
