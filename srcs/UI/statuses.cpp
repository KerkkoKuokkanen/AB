
#include "../../hdr/global.h"

bool compareStatuses(const t_StatSpriteStruct &obj1, const t_StatSpriteStruct &obj2)
{
	if (obj1.statusType < obj2.statusType)
		return (true);
	return (false);
}

static int numDigits(int num)
{
	if (num < 10)
		return (0);
	if (num < 100)
		return (1);
	if (num < 1000)
		return (2);
	return (3);
}

bool Statuses::GetMouseOverStatuses()
{
	int x = gameState.keys.staticMouseX;
	int y = gameState.keys.staticMouseY;
	for (int i = 0; i < statuses.size(); i++)
	{
		switch (statuses[i].statusType)
		{
			case StatusSigns::BURN:
			{
				const SDL_Rect tmp1 = statuses[i].images.sprite->dest;
				const SDL_FRect hld1 = staitcTranslateSprite(tmp1);
				const SDL_Rect dst1 = {(int)hld1.x, (int)hld1.y, (int)hld1.w, (int)hld1.h};
				if (MenuHoverCheck(gameState.surfaces.statuses.burn, dst1, x, y))
					return (true);
				break ;
			}
			case StatusSigns::STUN:
			{
				const SDL_Rect tmp1 = statuses[i].images.sprite->dest;
				const SDL_FRect hld1 = staitcTranslateSprite(tmp1);
				const SDL_Rect dst1 = {(int)hld1.x, (int)hld1.y, (int)hld1.w, (int)hld1.h};
				if (MenuHoverCheck(gameState.surfaces.statuses.questionMark, dst1, x, y))
					return (true);
				break ;
			}
			case StatusSigns::BUFF:
			{
				SDL_Rect dest = statuses[i].images.sprite->dest;
				const SDL_FRect hld1 = staitcTranslateSprite(dest);
				SDL_Point test = {x, y};
				SDL_Rect used = {(int)hld1.x, (int)hld1.y, (int)hld1.w, (int)hld1.h};
				if (pointCheck(test, used))
					return (true);
				break ;
			}
			case StatusSigns::DEBUFF:
			{
				SDL_Rect dest = statuses[i].images.sprite->dest;
				const SDL_FRect hld1 = staitcTranslateSprite(dest);
				SDL_Point test = {x, y};
				SDL_Rect used = {(int)hld1.x, (int)hld1.y, (int)hld1.w, (int)hld1.h};
				if (pointCheck(test, used))
					return (true);
				break ;
			}
			case StatusSigns::HOST:
			{
				const SDL_Rect tmp1 = statuses[i].images.sprite->dest;
				const SDL_FRect hld1 = staitcTranslateSprite(tmp1);
				const SDL_Rect dst1 = {(int)hld1.x, (int)hld1.y, (int)hld1.w, (int)hld1.h};
				if (MenuHoverCheck(gameState.surfaces.hostSymbol, dst1, x, y))
					return (true);
				break ;
			}
			case StatusSigns::HOSTING:
			{
				const SDL_Rect tmp1 = statuses[i].images.sprite->dest;
				const SDL_FRect hld1 = staitcTranslateSprite(tmp1);
				const SDL_Rect dst1 = {(int)hld1.x, (int)hld1.y, (int)hld1.w, (int)hld1.h};
				if (MenuHoverCheck(gameState.surfaces.hostingSymbol, dst1, x, y))
					return (true);
				break ;
			}
			case StatusSigns::TOXIC_BLADE:
			{
				const SDL_Rect tmp1 = statuses[i].images.sprite->dest;
				const SDL_FRect hld1 = staitcTranslateSprite(tmp1);
				const SDL_Rect dst1 = {(int)hld1.x, (int)hld1.y, (int)hld1.w, (int)hld1.h};
				if (MenuHoverCheck(gameState.surfaces.toxinSym, dst1, x, y))
					return (true);
				break ;
			}
			case StatusSigns::POISON:
			{
				const SDL_Rect tmp1 = statuses[i].images.sprite->dest;
				const SDL_FRect hld1 = staitcTranslateSprite(tmp1);
				const SDL_Rect dst1 = {(int)hld1.x, (int)hld1.y, (int)hld1.w, (int)hld1.h};
				if (MenuHoverCheck(gameState.surfaces.poisonSym, dst1, x, y))
					return (true);
				break ;
			}
			case StatusSigns::BLEED:
			{
				const SDL_Rect tmp1 = statuses[i].images.sprite->dest;
				const SDL_FRect hld1 = staitcTranslateSprite(tmp1);
				const SDL_Rect dst1 = {(int)hld1.x, (int)hld1.y, (int)hld1.w, (int)hld1.h};
				if (MenuHoverCheck(gameState.surfaces.bleedSymbol, dst1, x, y))
					return (true);
				break ;
			}
			case StatusSigns::SLOWED:
			{
				const SDL_Rect tmp1 = statuses[i].images.sprite->dest;
				const SDL_FRect hld1 = staitcTranslateSprite(tmp1);
				const SDL_Rect dst1 = {(int)hld1.x, (int)hld1.y, (int)hld1.w, (int)hld1.h};
				if (MenuHoverCheck(gameState.surfaces.slowSymbol, dst1, x, y))
					return (true);
				break ;
			}
		}
	}
	return (false);
}

void Statuses::CreateBurns()
{
	SDL_Rect dest = {0, 0, size, size};
	if (character->statuses.burns.size() > 0)
	{
		t_SnippetAndSprite add;
		add.sprite = new Sprite(gameState.textures.statuses.burns[2], dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
		add.sprite->orderLayer = 1;
		gameState.render->AddSprite(add.sprite, TURN_ORDER_LAYER);
		int num = (int)character->statuses.burns.size();
		if (num > 0)
		{
			num = (num > 999) ? 999 : num;
			std::string used = std::to_string(num);
			const char *text = used.c_str();
			add.snippet = new Snippet(text, FontTypes::GOOGLE_TEXT, true, {0, 0}, numberSize, numberOffset, TURN_ORDER_LAYER, true);
			add.snippet->SetOrderLayer(3);
			add.snippet->SetOutlineColor(25, 25, 25);
			add.snippet->SetAlphaMod(204);
		}
		else
			add.snippet = NULL;
		statuses.push_back({add, StatusSigns::BURN});
	}
}

void Statuses::CreateStatuses()
{
	CreateBurns();
}

Statuses::Statuses(Character *character, int size, int numberSize, int numOffset, bool staticSprite, bool vertical)
{
	if (size < 50)
		size = 1000;
	if (numberSize < 50)
		numberSize = 1000;
	Statuses::size = size;
	Statuses::numberSize = numberSize;
	Statuses::numberOffset = numOffset;
	Statuses::character = character;
	Statuses::vertical = vertical;
	Statuses::staticSprite = staticSprite;
	CreateStatuses();
	OrderStatuses();
}

void Statuses::OrderStatuses()
{
	if (statuses.size() < 2)
		return ;
	std::sort(statuses.begin(), statuses.end(), compareStatuses);
}

void Statuses::ChangeAmount(int &index, int amount, int num)
{
	statuses[index].amount = amount;
	if (statuses[index].images.snippet != NULL)
		delete statuses[index].images.snippet;
	if (amount == 0)
	{
		if (statuses[index].images.sprite != NULL)
			delete statuses[index].images.sprite;
		statuses.erase(statuses.begin() + index);
		index -= 1;
		return ;
	}
	std::string used = std::to_string(amount);
	const char *text = used.c_str();
	statuses[index].images.snippet = new Snippet(text, FontTypes::GOOGLE_TEXT, true, {0, 0}, numberSize, numberOffset, TURN_ORDER_LAYER, true);
	statuses[index].images.snippet->SetOrderLayer(3);
	statuses[index].images.snippet->SetOutlineColor(50, 50, 50);
	statuses[index].images.snippet->SetAlphaMod(200);
	RePosition();
}

SDL_Rect Statuses::GetRightRect(int statusSign)
{
	SDL_Rect ret = {0, 0, 0, 0};
	for (int i = 0; i < statuses.size(); i++)
	{
		if (statuses[i].statusType == statusSign)
		{
			ret = statuses[i].images.sprite->dest;
			break ;
		}
	}
	return (ret);
}

void Statuses::Postion(Vector place)
{
	positioned = true;
	position = {place.x, place.y};
	if (statuses.size() == 0)
		return ;
	OrderStatuses();
	float diff = (float)size;
	for (int i = 0; i < statuses.size(); i++)
	{
		statuses[i].images.sprite->Position(Vector(place.x + (diff * i), place.y));
		if (statuses[i].images.snippet == NULL)
			continue ;
		float x = (float)statuses[i].images.sprite->dest.x - ((int)((float)numberOffset * 1.6f) * ((float)numDigits(statuses[i].amount) * 0.1f));
		statuses[i].images.snippet->Position({rounding(x), rounding(place.y) - numberSize / 4});
	}
}

void Statuses::RePosition()
{
	if (statuses.size() == 0)
		return ;
	OrderStatuses();
	if (positioned)
		Postion(Vector((float)position.x, (float)position.y));
	else
	{
		SDL_Rect dest = statuses[0].images.sprite->dest;
		Postion(Vector((float)dest.x, (float)dest.y));
	}
}

void Statuses::Update()
{
	CheckIfNewStatuses();
	CheckIfNeedToCreateStatuses();
}

bool Statuses::AlreadyExists(int statusSign)
{
	for (int i = 0; i < statuses.size(); i++)
	{
		if (statuses[i].statusType == statusSign)
			return (true);
	}
	return (false);
}

void Statuses::CreateFrestStatus(int statusSign)
{
	t_SnippetAndSprite add;
	SDL_Rect dest = {0, 0, size, size};
	bool onlyOne = false;
	if (statuses.size() == 0)
		onlyOne = true;
	switch (statusSign)
	{
		case StatusSigns::BURN:
		{
			add.sprite = new Sprite(gameState.textures.statuses.burns[2], dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
			add.sprite->orderLayer = 1;
			gameState.render->AddSprite(add.sprite, TURN_ORDER_LAYER);
			int num = (int)character->statuses.burns.size();
			if (num > 0)
			{
				num = (num > 999) ? 999 : num;
				std::string used = std::to_string(num);
				const char *text = used.c_str();
				add.snippet = new Snippet(text, FontTypes::GOOGLE_TEXT, true, {0, 0}, numberSize, numberOffset, TURN_ORDER_LAYER, true);
				add.snippet->SetOrderLayer(3);
				add.snippet->SetOutlineColor(50, 50, 50);
				add.snippet->SetAlphaMod(200);
			}
			else
				add.snippet = NULL;
			statuses.push_back({add, StatusSigns::BURN, num});
			break ;
		}
		case StatusSigns::STUN:
		{
			add.sprite = new Sprite(gameState.textures.questionMark, dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
			add.sprite->orderLayer = 1;
			gameState.render->AddSprite(add.sprite, TURN_ORDER_LAYER);
			add.snippet = NULL;
			statuses.push_back({add, StatusSigns::STUN, 1});
			break ;
		}
		case StatusSigns::BUFF:
		{
			add.sprite = new Sprite(gameState.textures.buffSymbol, dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
			add.sprite->orderLayer = 1;
			add.sprite->ColorMod(23, 96, 255);
			gameState.render->AddSprite(add.sprite, TURN_ORDER_LAYER);
			add.snippet = NULL;
			statuses.push_back({add, StatusSigns::BUFF, 1});
			break ;
		}
		case StatusSigns::DEBUFF:
		{
			add.sprite = new Sprite(gameState.textures.buffSymbol, dest, NULL, NULL, 0, FLIP_VERTICAL, staticSprite);
			add.sprite->orderLayer = 1;
			add.sprite->ColorMod(255, 60, 22);
			gameState.render->AddSprite(add.sprite, TURN_ORDER_LAYER);
			add.snippet = NULL;
			statuses.push_back({add, StatusSigns::DEBUFF, 1});
			break ;
		}
		case StatusSigns::HOST:
		{
			add.sprite = new Sprite(gameState.textures.hostSymbol, dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
			add.sprite->orderLayer = 1;
			gameState.render->AddSprite(add.sprite, TURN_ORDER_LAYER);
			add.snippet = NULL;
			statuses.push_back({add, StatusSigns::HOST, 1});
			break ;
		}
		case StatusSigns::HOSTING:
		{
			add.sprite = new Sprite(gameState.textures.hostingSymbol, dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
			add.sprite->orderLayer = 1;
			gameState.render->AddSprite(add.sprite, TURN_ORDER_LAYER);
			add.snippet = NULL;
			statuses.push_back({add, StatusSigns::HOSTING, 1});
			break ;
		}
		case StatusSigns::TOXIC_BLADE:
		{
			add.sprite = new Sprite(gameState.textures.toxinSymbol, dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
			add.sprite->orderLayer = 1;
			gameState.render->AddSprite(add.sprite, TURN_ORDER_LAYER);
			int num = (int)character->statuses.toxicBlade.size();
			if (num > 0)
			{
				num = (num > 999) ? 999 : num;
				std::string used = std::to_string(num);
				const char *text = used.c_str();
				add.snippet = new Snippet(text, FontTypes::GOOGLE_TEXT, true, {0, 0}, numberSize, numberOffset, TURN_ORDER_LAYER, true);
				add.snippet->SetOrderLayer(3);
				add.snippet->SetOutlineColor(50, 50, 50);
				add.snippet->SetAlphaMod(200);
			}
			else
				add.snippet = NULL;
			statuses.push_back({add, StatusSigns::TOXIC_BLADE, num});
			break ;
		}
		case StatusSigns::POISON:
		{
			add.sprite = new Sprite(gameState.textures.poisonSymbol, dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
			add.sprite->orderLayer = 1;
			gameState.render->AddSprite(add.sprite, TURN_ORDER_LAYER);
			int num = (int)character->statuses.poison.size();
			if (num > 0)
			{
				num = (num > 999) ? 999 : num;
				std::string used = std::to_string(num);
				const char *text = used.c_str();
				add.snippet = new Snippet(text, FontTypes::GOOGLE_TEXT, true, {0, 0}, numberSize, numberOffset, TURN_ORDER_LAYER, true);
				add.snippet->SetOrderLayer(3);
				add.snippet->SetOutlineColor(50, 50, 50);
				add.snippet->SetAlphaMod(200);
			}
			else
				add.snippet = NULL;
			statuses.push_back({add, StatusSigns::POISON, num});
			break ;
		}
		case StatusSigns::BLEED:
		{
			add.sprite = new Sprite(gameState.textures.bleedSymbol, dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
			add.sprite->orderLayer = 1;
			gameState.render->AddSprite(add.sprite, TURN_ORDER_LAYER);
			int num = (int)character->statuses.bleed.size();
			if (num > 0)
			{
				num = (num > 999) ? 999 : num;
				std::string used = std::to_string(num);
				const char *text = used.c_str();
				add.snippet = new Snippet(text, FontTypes::GOOGLE_TEXT, true, {0, 0}, numberSize, numberOffset, TURN_ORDER_LAYER, true);
				add.snippet->SetOrderLayer(3);
				add.snippet->SetOutlineColor(50, 50, 50);
				add.snippet->SetAlphaMod(200);
			}
			else
				add.snippet = NULL;
			statuses.push_back({add, StatusSigns::BLEED, num});
			break ;
		}
		case StatusSigns::SLOWED:
		{
			add.sprite = new Sprite(gameState.textures.slowSymbol, dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
			add.sprite->orderLayer = 1;
			gameState.render->AddSprite(add.sprite, TURN_ORDER_LAYER);
			add.snippet = NULL;
			statuses.push_back({add, StatusSigns::SLOWED, 1});
			break ;
		}
	}
	if (onlyOne)
	{
		Postion(Vector(position.x, position.y));
		return ;
	}
	RePosition();
}

void Statuses::CheckIfNeedToCreateStatuses()
{
	if (character->statuses.burns.size() != 0)
	{
		if (!AlreadyExists(StatusSigns::BURN))
			CreateFrestStatus(StatusSigns::BURN);
	}
	if (character->statuses.stun != 0)
	{
		if (!AlreadyExists(StatusSigns::STUN))
			CreateFrestStatus(StatusSigns::STUN);
	}
	if (character->statuses.buffs.size() != 0)
	{
		if (!AlreadyExists(StatusSigns::BUFF))
			CreateFrestStatus(StatusSigns::BUFF);
	}
	if (character->statuses.deBuffs.size() != 0)
	{
		if (!AlreadyExists(StatusSigns::DEBUFF))
			CreateFrestStatus(StatusSigns::DEBUFF);
	}
	if (character->statuses.hosted)
	{
		if (!AlreadyExists(StatusSigns::HOST))
			CreateFrestStatus(StatusSigns::HOST);
	}
	if (character->statuses.hosting != NULL)
	{
		if (!AlreadyExists(StatusSigns::HOSTING))
			CreateFrestStatus(StatusSigns::HOSTING);
	}
	if (character->statuses.toxicBlade.size() != 0)
	{
		if (!AlreadyExists(StatusSigns::TOXIC_BLADE))
			CreateFrestStatus(StatusSigns::TOXIC_BLADE);
	}
	if (character->statuses.poison.size() != 0)
	{
		if (!AlreadyExists(StatusSigns::POISON))
			CreateFrestStatus(StatusSigns::POISON);
	}
	if (character->statuses.bleed.size() != 0)
	{
		if (!AlreadyExists(StatusSigns::BLEED))
			CreateFrestStatus(StatusSigns::BLEED);
	}
	if (character->statuses.slowed != 0)
	{
		if (!AlreadyExists(StatusSigns::SLOWED))
			CreateFrestStatus(StatusSigns::SLOWED);
	}
}

void Statuses::CheckIfNewStatuses()
{
	for (int i = 0; i < statuses.size(); i++)
	{
		switch (statuses[i].statusType)
		{
			case StatusSigns::BURN:
			{
				int amount = (int)character->statuses.burns.size();
				amount = (amount > 999) ? 999 : amount;
				int num = (statuses[i].images.snippet == NULL) ? 0 : statuses[i].amount;
				if (amount != num)
					ChangeAmount(i, amount, num);
				break ;
			}
			case StatusSigns::STUN:
			{
				if (character->statuses.stun == 0 && AlreadyExists(StatusSigns::STUN))
					ChangeAmount(i, 0, 0);
				break ;
			}
			case StatusSigns::BUFF:
			{
				if (character->statuses.buffs.size() == 0 && AlreadyExists(StatusSigns::BUFF))
					ChangeAmount(i, 0, 0);
				break ;
			}
			case StatusSigns::DEBUFF:
			{
				if (character->statuses.buffs.size() == 0 && AlreadyExists(StatusSigns::DEBUFF))
					ChangeAmount(i, 0, 0);
				break ;
			}
			case StatusSigns::HOST:
			{
				if (character->statuses.hosted == false && AlreadyExists(StatusSigns::HOST))
					ChangeAmount(i, 0, 0);
				break ;
			}
			case StatusSigns::HOSTING:
			{
				if (character->statuses.hosting == NULL && AlreadyExists(StatusSigns::HOSTING))
					ChangeAmount(i, 0, 0);
				break ;
			}
			case StatusSigns::TOXIC_BLADE:
			{
				int amount = (int)character->statuses.toxicBlade.size();
				amount = (amount > 999) ? 999 : amount;
				int num = (statuses[i].images.snippet == NULL) ? 0 : statuses[i].amount;
				if (amount != num)
					ChangeAmount(i, amount, num);
				break ;
			}
			case StatusSigns::POISON:
			{
				int amount = (int)character->statuses.poison.size();
				amount = (amount > 999) ? 999 : amount;
				int num = (statuses[i].images.snippet == NULL) ? 0 : statuses[i].amount;
				if (amount != num)
					ChangeAmount(i, amount, num);
				break ;
			}
			case StatusSigns::BLEED:
			{
				int amount = (int)character->statuses.bleed.size();
				amount = (amount > 999) ? 999 : amount;
				int num = (statuses[i].images.snippet == NULL) ? 0 : statuses[i].amount;
				if (amount != num)
					ChangeAmount(i, amount, num);
				break ;
			}
			case StatusSigns::SLOWED:
			{
				if (character->statuses.slowed == 0 && AlreadyExists(StatusSigns::SLOWED))
					ChangeAmount(i, 0, 0);
				break ;
			}
		}
	}
}

void Statuses::Destroy()
{
	for (int i = 0; i < statuses.size(); i++)
	{
		if (statuses[i].images.sprite != NULL)
			delete statuses[i].images.sprite;
		if (statuses[i].images.snippet != NULL)
			delete statuses[i].images.snippet;
	}
	statuses.clear();
}
