
#include "../../../hdr/global.h"
#define TB 1400
#define TBO 700
#define TN 1100
#define TNO 550

static std::string GetTurnText(int small, int big)
{
	if (small == big)
	{
		std::string ret = std::to_string(small);
		ret += " Turns";
		return (ret);
	}
	std::string ret = std::to_string(small);
	ret += "-";
	ret += std::to_string(big);
	ret += " Turns";
	return (ret);
}

int TTBuffAccuracy(Character *character, TextBubble *bubble, int start)
{
	int amont = 0;
	int turnsMin = 1000, turnsMax = 0;
	for (int i = 0; i < character->statuses.buffs.size(); i++)
	{
		if (character->statuses.buffs[i].type == BuffTypes::ACCURACY)
		{
			int t = character->statuses.buffs[i].turns;
			amont += character->statuses.buffs[i].amount;
			if (t > turnsMax)
				turnsMax = t;
			if (t < turnsMin)
				turnsMin = t;
		}
	}
	if (amont == 0)
		return (start);
	std::string turns = GetTurnText(turnsMin, turnsMax);
	Snippet *add1 = new Snippet("Accuracy:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add15 = new Snippet(turns.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	std::string strstr = std::to_string(amont);
	strstr += "% increaced chance";
	Snippet *add2 = new Snippet(strstr.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add3 = new Snippet("to land attacks", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	bubble->AddSnippetToBubble(add1, {500, start});
	bubble->AddSnippetToBubble(add15, {5900, start});
	start += 2000;
	bubble->AddSnippetToBubble(add2, {500, start});
	start += 1500;
	bubble->AddSnippetToBubble(add3, {500, start});
	start += 3000;
	return (start);
}

int TTBuffOppAccuracy(Character *character, TextBubble *bubble, int start)
{
	int amont = 0;
	int turnsMin = 1000, turnsMax = 0;
	for (int i = 0; i < character->statuses.buffs.size(); i++)
	{
		if (character->statuses.buffs[i].type == BuffTypes::OPPORTUNITY_ACCURACY)
		{
			int t = character->statuses.buffs[i].turns;
			amont += character->statuses.buffs[i].amount;
			if (t > turnsMax)
				turnsMax = t;
			if (t < turnsMin)
				turnsMin = t;
		}
	}
	if (amont == 0)
		return (start);
	std::string turns = GetTurnText(turnsMin, turnsMax);
	Snippet *add1 = new Snippet("Opportunity Accuracy:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add15 = new Snippet(turns.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	std::string strstr = std::to_string(amont);
	strstr += "% increaced chance";
	Snippet *add2 = new Snippet(strstr.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add3 = new Snippet("to land opportunity attacks", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	bubble->AddSnippetToBubble(add1, {500, start});
	bubble->AddSnippetToBubble(add15, {12500, start});
	start += 2000;
	bubble->AddSnippetToBubble(add2, {500, start});
	start += 1500;
	bubble->AddSnippetToBubble(add3, {500, start});
	start += 3000;
	return (start);
}

int TTBuffProtection(Character *character, TextBubble *bubble, int start)
{
	int amont = 0;
	int turnsMin = 1000, turnsMax = 0;
	for (int i = 0; i < character->statuses.buffs.size(); i++)
	{
		if (character->statuses.buffs[i].type == BuffTypes::PROTECTION)
		{
			int t = character->statuses.buffs[i].turns;
			amont += character->statuses.buffs[i].amount;
			if (t > turnsMax)
				turnsMax = t;
			if (t < turnsMin)
				turnsMin = t;
		}
	}
	if (amont == 0)
		return (start);
	std::string turns = GetTurnText(turnsMin, turnsMax);
	Snippet *add1 = new Snippet("Protection:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add15 = new Snippet(turns.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	std::string strstr = std::to_string(amont);
	strstr += "% of incoming damage";
	Snippet *add2 = new Snippet(strstr.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add3 = new Snippet("from attacks is mitigated", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	bubble->AddSnippetToBubble(add1, {500, start});
	bubble->AddSnippetToBubble(add15, {7000, start});
	start += 2000;
	bubble->AddSnippetToBubble(add2, {500, start});
	start += 1500;
	bubble->AddSnippetToBubble(add3, {500, start});
	start += 3000;
	return (start);
}

int TTDeBuffAccuracy(Character *character, TextBubble *bubble, int start)
{
	int amont = 0;
	int turnsMin = 1000, turnsMax = 0;
	for (int i = 0; i < character->statuses.deBuffs.size(); i++)
	{
		if (character->statuses.deBuffs[i].type == BuffTypes::ACCURACY)
		{
			int t = character->statuses.deBuffs[i].turns;
			amont += character->statuses.deBuffs[i].amount;
			if (t > turnsMax)
				turnsMax = t;
			if (t < turnsMin)
				turnsMin = t;
		}
	}
	if (amont == 0)
		return (start);
	std::string turns = GetTurnText(turnsMin, turnsMax);
	Snippet *add1 = new Snippet("Accuracy:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add15 = new Snippet(turns.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	std::string strstr = std::to_string(amont);
	strstr += "% decreased chance";
	Snippet *add2 = new Snippet(strstr.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add3 = new Snippet("to land attacks", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	bubble->AddSnippetToBubble(add1, {500, start});
	bubble->AddSnippetToBubble(add15, {5900, start});
	start += 2000;
	bubble->AddSnippetToBubble(add2, {500, start});
	start += 1500;
	bubble->AddSnippetToBubble(add3, {500, start});
	start += 3000;
	return (start);
}

int TTDeBuffOppAccuracy(Character *character, TextBubble *bubble, int start)
{
	int amont = 0;
	int turnsMin = 1000, turnsMax = 0;
	for (int i = 0; i < character->statuses.deBuffs.size(); i++)
	{
		if (character->statuses.deBuffs[i].type == BuffTypes::OPPORTUNITY_ACCURACY)
		{
			int t = character->statuses.deBuffs[i].turns;
			amont += character->statuses.deBuffs[i].amount;
			if (t > turnsMax)
				turnsMax = t;
			if (t < turnsMin)
				turnsMin = t;
		}
	}
	if (amont == 0)
		return (start);
	std::string turns = GetTurnText(turnsMin, turnsMax);
	Snippet *add1 = new Snippet("Opportunity Accuracy:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add15 = new Snippet(turns.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	std::string strstr = std::to_string(amont);
	strstr += "% decreased chance";
	Snippet *add2 = new Snippet(strstr.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add3 = new Snippet("to land opportunity attacks", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	bubble->AddSnippetToBubble(add1, {500, start});
	bubble->AddSnippetToBubble(add15, {12500, start});
	start += 2000;
	bubble->AddSnippetToBubble(add2, {500, start});
	start += 1500;
	bubble->AddSnippetToBubble(add3, {500, start});
	start += 3000;
	return (start);
}

int TTDeBuffProtection(Character *character, TextBubble *bubble, int start)
{
	int amont = 0;
	int turnsMin = 1000, turnsMax = 0;
	for (int i = 0; i < character->statuses.deBuffs.size(); i++)
	{
		if (character->statuses.deBuffs[i].type == BuffTypes::PROTECTION)
		{
			int t = character->statuses.deBuffs[i].turns;
			amont += character->statuses.deBuffs[i].amount;
			if (t > turnsMax)
				turnsMax = t;
			if (t < turnsMin)
				turnsMin = t;
		}
	}
	if (amont == 0)
		return (start);
	std::string turns = GetTurnText(turnsMin, turnsMax);
	Snippet *add1 = new Snippet("Protection:", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add15 = new Snippet(turns.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	std::string strstr = std::to_string(amont);
	strstr += "% more incoming";
	Snippet *add2 = new Snippet(strstr.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add3 = new Snippet("damage from attacks", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	bubble->AddSnippetToBubble(add1, {500, start});
	bubble->AddSnippetToBubble(add15, {7000, start});
	start += 2000;
	bubble->AddSnippetToBubble(add2, {500, start});
	start += 1500;
	bubble->AddSnippetToBubble(add3, {500, start});
	start += 3000;
	return (start);
}
