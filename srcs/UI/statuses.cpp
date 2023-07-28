
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

void Statuses::CreateStatuses()
{
	SDL_Rect dest = {0, 0, size, size};
	if (character->statuses.burns.size() > 0)
	{
		t_NumberAndSprite add;
		add.sprite = new Sprite(gameState.textures.statuses.burns[2], dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
		add.sprite->orderLayer = 1;
		gameState.render->AddSprite(add.sprite, INFO_LAYER);
		int num = (int)character->statuses.burns.size();
		if (num > 0)
		{
			add.number = new Number(num, numberSize, INFO_LAYER, 2, staticSprite, NumberType::NORMAL);
			add.number->ColorMod(168, 168, 168);
		}
		else
			add.number = NULL;
		statuses.push_back({add, StatusSigns::BURN});
	}
}

Statuses::Statuses(Character *character, int size, int numberSize, bool staticSprite, bool vertical)
{
	if (size < 50)
		size = 1000;
	if (numberSize < 50)
		numberSize = 1000;
	Statuses::size = size;
	Statuses::numberSize = numberSize;
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
	if (statuses[index].images.number != NULL)
		delete statuses[index].images.number;
	if (amount == 0)
	{
		if (statuses[index].images.sprite != NULL)
			delete statuses[index].images.sprite;
		index -= 1;
		return ;
	}
	statuses[index].images.number = new Number(amount, numberSize, INFO_LAYER, 2, staticSprite, NumberType::NORMAL);
	statuses[index].images.number->ColorMod(168, 168, 168);
	if (gameState.screen.unit < 0.00002f)
		statuses[index].images.number->Deactivate();
	CreatePulser(statuses[index].statusType);
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

void Statuses::PositionPulsers()
{
	if (pulsers.size() == 0)
		return ;
	for (int i = 0; i < pulsers.size(); i++)
	{
		SDL_Rect dest = GetRightRect(pulsers[i].statusSign);
		pulsers[i].sprite->dest.x = dest.x - 100;
		pulsers[i].sprite->dest.y = dest.y - 100;
	}
}

void Statuses::Postion(Vector place)
{
	if (statuses.size() == 0)
	{
		position = {place.x, place.y};
		return ;
	}
	float diff = (float)size;
	for (int i = 0; i < statuses.size(); i++)
	{
		statuses[i].images.sprite->Position(Vector(place.x + (diff * i), place.y));
		if (statuses[i].images.number == NULL)
			continue ;
		float x = (float)statuses[i].images.sprite->dest.x - ((int)((float)numberSize * 0.9f) * numDigits(statuses[i].images.number->getNumber()));
		statuses[i].images.number->Position(Vector(x, place.y));
	}
	PositionPulsers();
}

void Statuses::RePosition()
{
	if (statuses.size() == 0)
		return ;
	OrderStatuses();
	SDL_Rect dest = statuses[0].images.sprite->dest;
	Postion(Vector((float)dest.x, (float)dest.y));
}

void Statuses::ManageNumbers()
{
	if (gameState.screen.unit < 0.00002f)
	{
		for (int i = 0; i < statuses.size(); i++)
		{
			if (statuses[i].images.number != NULL)
				statuses[i].images.number->Deactivate();
		}
	}
	else
	{
		for (int i = 0; i < statuses.size(); i++)
		{
			if (statuses[i].images.number != NULL)
				statuses[i].images.number->Activate();
		}
	}
}

void Statuses::CreatePulser(int statusSign)
{
	int index = 0;
	bool visited = false;
	for (int i = 0; i < statuses.size(); i++)
	{
		if (statuses[i].statusType == statusSign)
		{
			index = i;
			visited = true;
			break ;
		}
	}
	if (!visited)
		return ;
	for (int i = 0; i < pulsers.size(); i++)
	{
		if (pulsers[i].statusSign == statusSign)
		{
			pulsers[i].sprite->AlphaMod(0);
			pulsers[i].timer = 0;
			return ;
		}
	}
	SDL_Rect dest = statuses[index].images.sprite->dest;
	dest = {dest.x - 100, dest.y - 100, dest.w + 200, dest.h + 200};
	t_Pulser add;
	add.sprite = new Sprite(gameState.textures.statuses.burns[1], dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
	add.sprite->AlphaMod(0);
	add.sprite->ColorMod(200, 200, 200);
	gameState.render->AddSprite(add.sprite, INFO_LAYER);
	add.statusSign = statusSign;
	add.timer = 0;
	pulsers.push_back(add);
}

void Statuses::ManagePulsers()
{
	if (pulsers.size() == 0)
		return ;
	float unit = 255.0f / 15.0f;
	for (int i = 0; i < pulsers.size(); i++)
	{
		if (pulsers[i].timer <= 15)
		{
			int alpha = rounding((float)pulsers[i].timer * unit);
			if (alpha > 255)
				alpha = 255;
			pulsers[i].sprite->AlphaMod(alpha);
		}
		else if (pulsers[i].timer > 20)
		{
			int alpha = rounding((float)(15 - (pulsers[i].timer - 20)) * unit);
			if (alpha > 255)
				alpha = 255;
			pulsers[i].sprite->AlphaMod(alpha);
		}
		pulsers[i].timer++;
		if (pulsers[i].timer > 35)
		{
			delete pulsers[i].sprite;
			pulsers.erase(pulsers.begin() + i);
			i--;
		}
	}
}

void Statuses::Update()
{
	ManageNumbers();
	ManagePulsers();
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
	t_NumberAndSprite add;
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
			gameState.render->AddSprite(add.sprite, INFO_LAYER);
			int num = (int)character->statuses.burns.size();
			if (num > 0)
			{
				add.number = new Number(num, numberSize, INFO_LAYER, 2, staticSprite, NumberType::NORMAL);
				add.number->ColorMod(168, 168, 168);
				if (gameState.screen.unit < 0.00002f)
					add.number->Deactivate();
			}
			else
				add.number = NULL;
			statuses.push_back({add, StatusSigns::BURN});
			CreatePulser(StatusSigns::BURN);
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
				int num = (statuses[i].images.number == NULL) ? 0 : statuses[i].images.number->getNumber();
				if (amount != num)
					ChangeAmount(i, amount, num);
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
		if (statuses[i].images.number != NULL)
			delete statuses[i].images.number;
	}
	statuses.clear();
}
