
#include "../../hdr/global.h"

bool compareStatuses(const t_StatSpriteStruct &obj1, const t_StatSpriteStruct &obj2)
{
	if (obj1.statusType < obj2.statusType)
		return (true);
	return (false);
}

void Statuses::CreateStatuses()
{
	SDL_Rect dest = {0, 0, size, size};
	if (character->statuses.burns.size() > 0)
	{
		t_NumberAndSprite add;
		add.sprite = new Sprite(gameState.textures.statuses.burns[2], dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
		gameState.render->AddSprite(add.sprite, INFO_LAYER);
		int num = (int)character->statuses.burns.size();
		if (num > 0)
		{
			add.number = new Number(num, numberSize, INFO_LAYER, 1, staticSprite, NumberType::NORMAL);
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
	statuses[index].images.number = new Number(amount, numberSize, INFO_LAYER, 1, staticSprite, NumberType::NORMAL);
	statuses[index].images.number->ColorMod(168, 168, 168);
	RePosition();
}

void Statuses::Postion(Vector place)
{
	float diff = (float)size;
	for (int i = 0; i < statuses.size(); i++)
	{
		statuses[i].images.sprite->Position(Vector(place.x + (diff * i), place.y));
		if (statuses[i].images.number == NULL)
			continue ;
		float x = (float)statuses[i].images.sprite->dest.x;
		statuses[i].images.number->Position(Vector(x, place.y));
	}
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

void Statuses::Update()
{
	ManageNumbers();
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
	SDL_Rect dest = {0, 0, 1000, 1000};
	switch (statusSign)
	{
		case StatusSigns::BURN:
		{
			add.sprite = new Sprite(gameState.textures.statuses.burns[2], dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
			gameState.render->AddSprite(add.sprite, INFO_LAYER);
			int num = (int)character->statuses.burns.size();
			if (num > 0)
			{
				add.number = new Number(num, numberSize, INFO_LAYER, 1, staticSprite, NumberType::NORMAL);
				add.number->ColorMod(168, 168, 168);
			}
			else
				add.number = NULL;
			statuses.push_back({add, StatusSigns::BURN});
			break ;
		}
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
