
#include "../../../hdr/global.h"
#define TB 1400
#define TBO 700
#define TN 1100
#define TNO 550

static Character *AnyOneClicked()
{
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *character = gameState.battle.ground->characters[i].character;
		if (character->clicked)
			return (character);
	}
	return (NULL);
}

static std::string GetBurnTurnNumber()
{
	Character *click = AnyOneClicked();
	if (click == NULL)
		return ("");
	int small = 1000;
	int big = 0;
	for (int i = 0; i < click->statuses.burns.size(); i++)
	{
		int num = click->statuses.burns[i];
		if (num > big)
			big = num;
		if (num < small)
			small = num;
	}
	if (small == big)
	{
		std::string used = std::to_string(small);
		used += " Turns";
		return (used);
	}
	std::string used = std::to_string(small);
	used += "-";
	used += std::to_string(big);
	used += " Turns";
	return (used);
}

void StatusInfo::CreateBubbles(int hoverIcon)
{
	switch (hoverIcon)
	{
		case StatusSigns::BURN:
		{
			std::string ret = GetBurnTurnNumber();
			Snippet *add1 = new Snippet("Burn:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			Snippet *add15 = new Snippet(ret.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(240, 126, 0);
			Snippet *add2 = new Snippet("Target takes 5% extra", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add3 = new Snippet("damage from attacks", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add4 = new Snippet("for each stack", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSnippetToBubble(add1, {500, 250});
			bubble->AddSnippetToBubble(add15, {4600, 650});
			bubble->AddSnippetToBubble(add2, {500, 2750});
			bubble->AddSnippetToBubble(add3, {500, 4250});
			bubble->AddSnippetToBubble(add4, {500, 5750});
			break ;
		}
	}
}
