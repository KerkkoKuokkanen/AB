
#include "../../hdr/global.h"
#define SCALE_FACTOR 700.0f

static std::string GetText(Character *character)
{
	int level = character->stats.level;
	std::string text = "Turn: Level ";
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
	}
	return (text);
}

static SDL_Rect GetTextDest(std::string &str)
{
	SDL_Rect ret = {-41500, 44200, 0, 2200};
	int len = str.length();
	float width = (float)len * SCALE_FACTOR;
	ret.w = rounding(width);
	ret.x -= rounding(width / 2.0f);
	return (ret);
}

void CharacterUI::CreateTexts()
{
	std::string ret = GetText(activeCharacter);
	const char *str = ret.c_str();
	SDL_Rect dest = GetTextDest(ret);
	texts = get_text(str, FontTypes::GOOGLE_TEXT);
	text[0] = new Sprite(texts, dest, NULL, NULL, 0, FLIP_NONE, true);
	text[0]->orderLayer = 1;
	text[0]->ColorMod(220, 220, 220);
	gameState.render->AddSprite(text[0], TURN_ORDER_LAYER);
	dest.x -= 110;
	text[1] = new Sprite(texts, dest, NULL, NULL, 0, FLIP_NONE, true);
	text[1]->ColorMod(1, 1, 1);
	gameState.render->AddSprite(text[1], TURN_ORDER_LAYER);
	dest.x += 220;
	text[2] = new Sprite(texts, dest, NULL, NULL, 0, FLIP_NONE, true);
	text[2]->ColorMod(1, 1, 1);
	gameState.render->AddSprite(text[2], TURN_ORDER_LAYER);
	dest.x -= 110;
	dest.y -= 110;
	text[3] = new Sprite(texts, dest, NULL, NULL, 0, FLIP_NONE, true);
	text[3]->ColorMod(1, 1, 1);
	gameState.render->AddSprite(text[3], TURN_ORDER_LAYER);
	dest.y += 220;
	text[4] = new Sprite(texts, dest, NULL, NULL, 0, FLIP_NONE, true);
	text[4]->ColorMod(1, 1, 1);
	gameState.render->AddSprite(text[4], TURN_ORDER_LAYER);
}

void CharacterUI::ManageTurnText()
{
	if (!turnActive)
	{
		for (int i = 0; i < 5; i++)
		{
			if (text[i] != NULL)
				delete text[i];
			text[i] = NULL;
		}
		if (texts != NULL)
		{
			SDL_DestroyTexture(texts);
			texts = NULL;
		}
		return ;
	}
	if (text[0] == NULL)
		CreateTexts();
}
