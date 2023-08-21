
#include "../../hdr/global.h"

#define SCALE_FACTOR 550.0f

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
	}
	return (text);
}

SDL_Rect InfoBar::GetTextDest(std::string &str)
{
	SDL_Rect ret = {0, -42400, 0, 1700};
	int len = str.length();
	float width = (float)len * SCALE_FACTOR;
	ret.w = rounding(width);
	ret.x -= rounding(width / 2.0f);
	return (ret);
}

void InfoBar::CreateText()
{
	std::string ret = GetText(character);
	const char *str = ret.c_str();
	SDL_Rect dest = GetTextDest(ret);
	SDL_Texture *texts = get_text(str, FontTypes::GOOGLE_TEXT);
	charText = texts;
	text[0] = new Sprite(texts, dest, NULL, NULL, 0, FLIP_NONE, true);
	text[0]->orderLayer = 1;
	text[0]->ColorMod(220, 220, 220);
	gameState.render->AddSprite(text[0], TURN_ORDER_LAYER);
	dest.x -= 100;
	text[1] = new Sprite(texts, dest, NULL, NULL, 0, FLIP_NONE, true);
	text[1]->ColorMod(1, 1, 1);
	gameState.render->AddSprite(text[1], TURN_ORDER_LAYER);
	dest.x += 200;
	text[2] = new Sprite(texts, dest, NULL, NULL, 0, FLIP_NONE, true);
	text[2]->ColorMod(1, 1, 1);
	gameState.render->AddSprite(text[2], TURN_ORDER_LAYER);
	dest.x -= 100;
	dest.y -= 100;
	text[3] = new Sprite(texts, dest, NULL, NULL, 0, FLIP_NONE, true);
	text[3]->ColorMod(1, 1, 1);
	gameState.render->AddSprite(text[3], TURN_ORDER_LAYER);
	dest.y += 200;
	text[4] = new Sprite(texts, dest, NULL, NULL, 0, FLIP_NONE, true);
	text[4]->ColorMod(1, 1, 1);
	gameState.render->AddSprite(text[4], TURN_ORDER_LAYER);
}

void InfoBar::CreateBars()
{
	SDL_Rect dest = {-12500, -38000, 25000, 1600};
	health = new Bar(dest, true);
	health->ChangeToSmallBar();
	dest.y -= 1780;
	armor = new Bar(dest, true);
	armor->ChangeToSmallBar();
}

InfoBar::InfoBar(Character *character)
{
	InfoBar::character = character;
	CreateText();
	CreateBars();
	outline = new Sprite(gameState.textures.everyColor, {-12600, -39600, 25200, 2400}, NULL, NULL, 0, FLIP_NONE, true);
	outline->orderLayer = (-1);
	gameState.render->AddSprite(outline, TURN_ORDER_LAYER);
}

void InfoBar::Update()
{
	health->Update(character, true);
	armor->Update(character, false);
}

void InfoBar::Destroy()
{
	for (int i = 0; i < 5; i++)
	{
		if (text[i] != NULL)
			delete text[i];
	}
	if (charText != NULL)
		SDL_DestroyTexture(charText);
	if (health != NULL)
		delete health;
	if (armor != NULL)
		delete armor;
	if (fatigue != NULL)
		delete fatigue;
	if (outline != NULL)
		delete outline;
}
