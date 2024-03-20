
#include "../../hdr/global.h"
#define SCALE_FACTOR 700.0f

static std::string GetText(Character *character)
{
	int level = character->stats.level;
	std::string text = "Level ";
	text += std::to_string(level);
	switch (character->cSing)
	{
		case THIEF:
			text += ": Thief";
			break ;
		case SKELE:
			text += ": Skeleton";
			break ;
		case PYRO:
			text += ": Pyro";
			break ;
		case LION:
			text += ": Lion";
			break ;
		case SMITH:
			text += ": Blacksmith";
			break ;
		case MAGE:
			text += ": Mage";
			break ;
		case RAIDER:
			text += ": Raider";
			break ;
		case ALCHEMIST:
			text += ": Alchemist";
			break ;
		case KNIGHT:
			text += ": Knight";
			break ;
		case WITCH:
			text += ": Witch";
			break ;
		case BIG_THUG:
			text += ": Big Thug";
			break ;
		case THUG:
			text += ": Thug";
			break ;
	}
	return (text);
}

static SDL_Rect GetTextDest(std::string &str)
{
	SDL_Rect ret = {-24380, 45080, 0, 1900};
	int len = str.length();
	float width = (float)len * SCALE_FACTOR;
	ret.w = rounding(width);
	return (ret);
}

void CharacterUI::CreateTexts()
{
	std::string ret = GetText(activeCharacter);
	const char *str = ret.c_str();
	SDL_Rect dest = GetTextDest(ret);
	texts = get_text(str, FontTypes::GOOGLE_TEXT);
	text = new Sprite(texts, dest, NULL, NULL, 0, FLIP_NONE, true);
	text->orderLayer = 7;
	text->ColorMod(1, 1, 1);
	text->AlphaMod(130);
	gameState.render->AddSprite(text, TURN_ORDER_LAYER);
}

void CharacterUI::ManageTurnText()
{
	if (!turnActive)
	{
		if (text != NULL)
			delete text;
		text = NULL;
		if (texts != NULL)
		{
			SDL_DestroyTexture(texts);
			texts = NULL;
		}
		return ;
	}
	if (text == NULL)
		CreateTexts();
}
