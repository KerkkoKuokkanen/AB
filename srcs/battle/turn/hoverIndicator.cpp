
#include "../../../hdr/global.h"
#define COUNT_TIME 18

static Character *FindHoveredCharacter()
{
	Character *hovered = NULL;
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		if (gameState.battle.ground->characters[i].character->hover)
		{
			hovered = gameState.battle.ground->characters[i].character;
			if (hovered->active == false)
				hovered = NULL;
			return (hovered);
		}
	}
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (gameState.battle.ground->map[i][j].marked &&
				gameState.battle.ground->map[i][j].character != NULL)
			{
				hovered = gameState.battle.ground->map[i][j].character;
				if (hovered->active == false)
					hovered = NULL;
				return (hovered);
			}
		}
	}
	hovered = NULL;
	return (hovered);
}

int TurnOrder::InActiveList(Character *hover)
{
	for (int i = 0; i < indicators.size(); i++)
	{
		if (indicators[i].active == false)
			continue ;
		if (indicators[i].indicator->dest.x < rounding((float)gameState.screen.width / 3.26f))
			continue ;
		if (indicators[i].indicator->dest.x > rounding((float)gameState.screen.width / 1.5f))
			continue ;
		if (indicators[i].character == hover)
			return (i);
	}
	return (-1);
}

int GetIndicatorY()
{
	float start = gameState.screen.height / 300.0f;
	float fadeMulti = cos(gameState.updateObjs.fadeIter * 2.0f) / 2.0f + 0.5f;
	float add = (gameState.screen.height / 300.0f) * fadeMulti;
	int arr = rounding(start + add);
	return (arr);
}

void TurnOrder::UpdateHoverIndicator()
{
	Character *hover = FindHoveredCharacter();
	if (turnStartActive || killActive || turnChange || hover == NULL)
	{
		hoverIndicator->Deactivate();
		hoverCounter = 0;
		return ;
	}
	int index = InActiveList(hover);
	if (index < 0)
	{
		hoverIndicator->Deactivate();
		hoverCounter = 0;
		return ;
	}
	hoverCounter++;
	if (hoverCounter < COUNT_TIME)
	{
		hoverIndicator->Deactivate();
		return ;
	}
	hoverIndicator->Activate();
	SDL_Rect dest = indicators[index].indicator->dest;
	float mid = (float)dest.x + ((float)dest.w / 2.0f);
	SDL_Rect sDest = hoverIndicator->dest;
	float sMid = (float)sDest.w / 2.0f;
	int place = rounding(mid - sMid);
	if (indicators[index].character->cSing == SKELE)
		place -= rounding((float)gameState.screen.width / 120.0f);
	hoverIndicator->dest.x = place;
	hoverIndicator->dest.y = GetIndicatorY();
}
