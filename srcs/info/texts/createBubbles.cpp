
#include "../../../hdr/global.h"
#define TB 1400
#define TBO 700
#define TN 1100
#define TNO 550

static Character *AnyOneClicked(bool turnerAss)
{
	if (turnerAss)
		return (gameState.updateObjs.UI->GetActiveCharacter());
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *character = gameState.battle.ground->characters[i].character;
		if (character->clicked)
			return (character);
	}
	return (NULL);
}

static std::string GetFrenzyTurnNumber(int amount, Character *click)
{
	if (click == NULL)
		return ("");
	std::string ret = std::to_string(amount);
	ret += " Turns";
	return (ret);
}

static std::string GetSlowTurnNumber(int slow, Character *click)
{
	if (click == NULL)
		return ("");
	std::string ret = std::to_string(slow);
	ret += " Turns";
	return (ret);
}

static std::string GetToxicBladeTurnNumber(std::vector<t_ToxicStat> &stack, Character *click)
{
	if (click == NULL)
		return ("");
	int small = 1000;
	int big = 0;
	for (int i = 0; i < stack.size(); i++)
	{
		int num = stack[i].turns;
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

static std::string GetStatusTurnNumber(std::vector<SDL_Point> &stack, Character *click)
{
	if (click == NULL)
		return ("");
	int small = 1000;
	int big = 0;
	for (int i = 0; i < stack.size(); i++)
	{
		int num = stack[i].y;
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

static std::string GetBurnTurnNumber(std::vector<int> &stack, Character *click)
{
	if (click == NULL)
		return ("");
	int small = 1000;
	int big = 0;
	for (int i = 0; i < stack.size(); i++)
	{
		int num = stack[i];
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

static int GetYMinus(int last)
{
	float value = -0.440508f * (float)last + 526.810176f;
	int ret = rounding(value);
	return (ret);
}

void StatusInfo::CreateBubbles(int hoverIcon)
{
	switch (hoverIcon)
	{
		case StatusSigns::BURN:
		{
			Character *click = AnyOneClicked(fromTurnerAss);
			std::string ret = GetBurnTurnNumber(click->statuses.burns, click);
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
			bubble->SetUpOutline(500, GetYMinus(5750));
			break ;
		}
		case StatusSigns::POISON:
		{
			Character *click = AnyOneClicked(fromTurnerAss);
			std::string ret = GetStatusTurnNumber(click->statuses.poison, click);
			Snippet *add1 = new Snippet("Poison:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			Snippet *add15 = new Snippet(ret.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(9, 150, 5);
			Snippet *add2 = new Snippet("Target takes health", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add3 = new Snippet("damage for each stack", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSnippetToBubble(add1, {500, 250});
			bubble->AddSnippetToBubble(add15, {6000, 650});
			bubble->AddSnippetToBubble(add2, {500, 2750});
			bubble->AddSnippetToBubble(add3, {500, 4250});
			bubble->SetUpOutline(500, GetYMinus(4250));
			break ;
		}
		case StatusSigns::BLEED:
		{
			Character *click = AnyOneClicked(fromTurnerAss);
			std::string ret = GetStatusTurnNumber(click->statuses.bleed, click);
			Snippet *add1 = new Snippet("Bleed:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			Snippet *add15 = new Snippet(ret.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(250, 0, 0);
			Snippet *add2 = new Snippet("Target takes health", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add3 = new Snippet("damage for each stack", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSnippetToBubble(add1, {500, 250});
			bubble->AddSnippetToBubble(add15, {5250, 650});
			bubble->AddSnippetToBubble(add2, {500, 2750});
			bubble->AddSnippetToBubble(add3, {500, 4250});
			bubble->SetUpOutline(500, GetYMinus(4250));
			break ;
		}
		case StatusSigns::STUN:
		{
			Snippet *add1 = new Snippet("Stun:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(224, 203, 7);
			Snippet *add2 = new Snippet("Target automatically", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add3 = new Snippet("passes next turn", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSnippetToBubble(add1, {500, 250});
			bubble->AddSnippetToBubble(add2, {500, 2750});
			bubble->AddSnippetToBubble(add3, {500, 4250});
			bubble->SetUpOutline(500, GetYMinus(4250));
			break ;
		}
		case StatusSigns::SLOWED:
		{
			Character *click = AnyOneClicked(fromTurnerAss);
			std::string ret = GetSlowTurnNumber(click->statuses.slowed, click);
			Snippet *add1 = new Snippet("Slow:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			Snippet *add15 = new Snippet(ret.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(73, 84, 252);
			Snippet *add2 = new Snippet("Moving costs twice", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add3 = new Snippet("as much for target", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSnippetToBubble(add1, {500, 250});
			bubble->AddSnippetToBubble(add15, {4550, 650});
			bubble->AddSnippetToBubble(add2, {500, 2750});
			bubble->AddSnippetToBubble(add3, {500, 4250});
			bubble->SetUpOutline(500, GetYMinus(4250));
			break ;
		}
		case StatusSigns::CONTROL:
		{
			Character *click = AnyOneClicked(fromTurnerAss);
			std::string ret = GetSlowTurnNumber(click->statuses.controlZone, click);
			Snippet *add1 = new Snippet("Control Zone:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			Snippet *add15 = new Snippet(ret.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(67, 242, 58);
			Snippet *add2 = new Snippet("Target controls larger", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add3 = new Snippet("area", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSnippetToBubble(add1, {500, 250});
			bubble->AddSnippetToBubble(add15, {10050, 650});
			bubble->AddSnippetToBubble(add2, {500, 2750});
			bubble->AddSnippetToBubble(add3, {500, 4250});
			bubble->SetUpOutline(500, GetYMinus(4250));
			break ;
		}
		case StatusSigns::TOXIC_BLADE:
		{
			Character *click = AnyOneClicked(fromTurnerAss);
			std::string ret = GetToxicBladeTurnNumber(click->statuses.toxicBlade, click);
			Snippet *add1 = new Snippet("Toxic Blade:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			Snippet *add15 = new Snippet(ret.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(67, 242, 58);
			Snippet *add2 = new Snippet("Target applies poison", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add3 = new Snippet("with attacks", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSnippetToBubble(add1, {500, 250});
			bubble->AddSnippetToBubble(add15, {9400, 650});
			bubble->AddSnippetToBubble(add2, {500, 2750});
			bubble->AddSnippetToBubble(add3, {500, 4250});
			bubble->SetUpOutline(500, GetYMinus(4250));
			break ;
		}
		case StatusSigns::HOST:
		{
			Snippet *add1 = new Snippet("Hosted:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(255, 10, 246);
			Snippet *add2 = new Snippet("Target has 15%", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add3 = new Snippet("accuracy debuff", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add4 = new Snippet("Status ends when", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add5 = new Snippet("the caster gets", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add6 = new Snippet("hit or changes", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add7 = new Snippet("target", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSnippetToBubble(add1, {500, 250});
			bubble->AddSnippetToBubble(add2, {500, 2750});
			bubble->AddSnippetToBubble(add3, {500, 4250});
			bubble->AddSnippetToBubble(add4, {500, 6000});
			bubble->AddSnippetToBubble(add5, {500, 7500});
			bubble->AddSnippetToBubble(add6, {500, 9000});
			bubble->AddSnippetToBubble(add7, {500, 10500});
			bubble->SetUpOutline(500, GetYMinus(10500));
			break ;
		}
		case StatusSigns::HOSTING:
		{
			Snippet *add1 = new Snippet("Hosting:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(255, 10, 246);
			Snippet *add2 = new Snippet("Extends targets", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add3 = new Snippet("range of attacks", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add4 = new Snippet("Status ends when", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add5 = new Snippet("the caster is", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add6 = new Snippet("hit by an attack", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSnippetToBubble(add1, {500, 250});
			bubble->AddSnippetToBubble(add2, {500, 2750});
			bubble->AddSnippetToBubble(add3, {500, 4250});
			bubble->AddSnippetToBubble(add4, {500, 6000});
			bubble->AddSnippetToBubble(add5, {500, 7500});
			bubble->AddSnippetToBubble(add6, {500, 9000});
			bubble->SetUpOutline(500, GetYMinus(9000));
			break ;
		}
		case StatusSigns::BUFF:
		{
			int start = 2750;
			Character *click = AnyOneClicked(fromTurnerAss);
			Snippet *add1 = new Snippet("Buffs:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(56, 119, 255);
			bubble->AddSnippetToBubble(add1, {500, 250});
			start = TTBuffAccuracy(click, bubble, start);
			start = TTBuffOppAccuracy(click, bubble, start);
			start = TTBuffProtection(click, bubble, start);
			start -= 3000;
			bubble->SetUpOutline(500, GetYMinus(start));
			break ;
		}
		case StatusSigns::DEBUFF:
		{
			int start = 2750;
			Character *click = AnyOneClicked(fromTurnerAss);
			Snippet *add1 = new Snippet("Debuffs:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(235, 47, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			start = TTDeBuffAccuracy(click, bubble, start);
			start = TTDeBuffOppAccuracy(click, bubble, start);
			start = TTDeBuffProtection(click, bubble, start);
			start -= 3000;
			bubble->SetUpOutline(500, GetYMinus(start));
			break ;
		}
		case StatusSigns::FRENZY:
		{
			Character *click = AnyOneClicked(fromTurnerAss);
			std::string ret = GetFrenzyTurnNumber(click->statuses.frenzy, click);
			Snippet *add1 = new Snippet("Frenzy:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			Snippet *add15 = new Snippet(ret.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(237, 14, 14);
			Snippet *plus1 = new Snippet("+", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, 1500, 750, TEXT_BUBBLE_LAYER, true);
			Snippet *plus2 = new Snippet("+", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, 1500, 750, TEXT_BUBBLE_LAYER, true);
			Snippet *add2 = new Snippet("50% damage increase", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add3 = new Snippet("10% critical chance", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSnippetToBubble(plus1, {500, 2350});
			bubble->AddSnippetToBubble(plus2, {500, 3850});
			bubble->AddSnippetToBubble(add1, {500, 250});
			bubble->AddSnippetToBubble(add15, {5800, 650});
			bubble->AddSnippetToBubble(add2, {1400, 2750});
			bubble->AddSnippetToBubble(add3, {1400, 4250});
			bubble->SetUpOutline(500, GetYMinus(4250));
			break ;
		}
		case StatusSigns::BIG_CHARACTER:
		{
			Snippet *add1 = new Snippet("Big Character:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(245, 199, 15);
			Snippet *add2 = new Snippet("Smaller characters can not", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add3 = new Snippet("stop this characters movement.", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add4 = new Snippet("Abilities involving movement", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add5 = new Snippet("may have smaller success rate", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			Snippet *add6 = new Snippet("or not work at all.", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSnippetToBubble(add1, {500, 250});
			bubble->AddSnippetToBubble(add2, {500, 2750});
			bubble->AddSnippetToBubble(add3, {500, 4250});
			bubble->AddSnippetToBubble(add4, {500, 6000});
			bubble->AddSnippetToBubble(add5, {500, 7500});
			bubble->AddSnippetToBubble(add6, {500, 9000});
			bubble->SetUpOutline(500, GetYMinus(9000));
			break ;
		}
	}
}
