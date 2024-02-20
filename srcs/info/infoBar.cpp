
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
		case PHANTOM_LION:
			text = "Phantom";
			break ;
		case TOOLS:
			text = "Toolbox";
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
	}
	return (text);
}

SDL_Rect InfoBar::GetTextDest(std::string &str)
{
	SDL_Rect ret = {0, -42380, 0, 1700};
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
	text[0]->ColorMod(250, 250, 250);
	gameState.render->AddSprite(text[0], TURN_ORDER_LAYER);
	dest.x -= 100;
	dest.y -= 100;
	text[1] = new Sprite(texts, dest, NULL, NULL, 0, FLIP_NONE, true);
	text[1]->ColorMod(40, 40, 40);
	gameState.render->AddSprite(text[1], TURN_ORDER_LAYER);
	dest.x += 200;
	text[2] = new Sprite(texts, dest, NULL, NULL, 0, FLIP_NONE, true);
	text[2]->ColorMod(40, 40, 40);
	gameState.render->AddSprite(text[2], TURN_ORDER_LAYER);
	dest.x -= 200;
	dest.y += 200;
	text[3] = new Sprite(texts, dest, NULL, NULL, 0, FLIP_NONE, true);
	text[3]->ColorMod(40, 40, 40);
	gameState.render->AddSprite(text[3], TURN_ORDER_LAYER);
	dest.x += 200;
	text[4] = new Sprite(texts, dest, NULL, NULL, 0, FLIP_NONE, true);
	text[4]->ColorMod(40, 40, 40);
	gameState.render->AddSprite(text[4], TURN_ORDER_LAYER);
}

void InfoBar::CreateBars()
{
	SDL_Rect dest = {-12500, -37860, 25000, 1600};
	health = new Bar(dest, true);
	health->ChangeToSmallBar();
	health->slash->dest.w += 80;
	health->leftNumberOffset = {-300, 20};
	health->rightNumberOffset = {900, 20};
	dest.y -= 1780;
	if (character->cSing != PHANTOM_LION && character->cSing != TOOLS)
	{
		dest.w /= 2;
		dest.h -= 70;
		armor = new Bar(dest, true);
		armor->ChangeToSmallBar();
		armor->ChangeTextureToNarrow();
		armor->leftNumberOffset = {-230, -100};
		armor->rightNumberOffset = {850, -100};
		dest.x = 0;
		fatigue = new FatigueBar(dest);
		fatigue->SmallerNumbers();
		fatigue->leftNumberOffset = {-230, -100};
		fatigue->rightNumberOffset = {850, - 100};
		fatigue->slash->dest.w += 400;
		fatigue->slash->dest.y -= 80;
		return ;
	}
	armor = new Bar(dest, true);
	armor->ChangeToSmallBar();
	armor->slash->dest.w += 80;
	armor->leftNumberOffset = {-300, -100};
	armor->rightNumberOffset = {900, -100};
}

InfoBar::InfoBar(Character *character)
{
	InfoBar::character = character;
	CreateText();
	CreateBars();
	outline = new Sprite(gameState.textures.everyColor, {-12600, -39440, 25200, 2380}, NULL, NULL, 0, FLIP_NONE, true);
	outline->orderLayer = (-1);
	outline->ColorMod(40, 40, 40);
	gameState.render->AddSprite(outline, TURN_ORDER_LAYER);
	statuses = new Statuses(character, 1800, 1080, 570, true);
	statuses->Postion(Vector(-12500.0f, -35200.0f));
}

void InfoBar::CheckMouseOver()
{
	if (!statBars)
		return ;
	over = false;
	SDL_Rect outline = {-12600, -39440, 25200, 2380};
	SDL_FRect hold = staitcTranslateSprite(outline);
	SDL_Rect real = {(int)hold.x, (int)hold.y, (int)hold.w, (int)hold.h};
	int x = gameState.keys.staticMouseX, y = gameState.keys.staticMouseY;
	SDL_Point check = {x, y};
	if (pointCheck(check, real))
		over = true;
	if (statuses->GetMouseOverStatuses())
		over = true;
}

void InfoBar::Update()
{
	health->Update(character, true);
	armor->Update(character, false);
	statuses->Update();
	CheckMouseOver();
	if (fatigue != NULL)
		fatigue->Update(character);
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
	if (statuses != NULL)
		delete statuses;
}
