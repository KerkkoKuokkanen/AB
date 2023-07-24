
#include "../../hdr/global.h"

Number::Number(int number, int size, int layer, int orderingLayer, bool staticSprite, int numberType)
{
	SDL_Rect dest = {0, 0, size, size};
	int offset = rounding((float)size + (float)size * 0.1f);
	std::string digits = std::to_string(number);
	int iterator = 0;
	for (char digit : digits)
	{
		int num = digit - '0';
		dest.x = offset * iterator;
		Sprite *sprite = new Sprite(gameState.textures.ascii.whiteNumbers[num], dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
		gameState.render->AddSprite(sprite, layer);
		sprite->orderLayer = orderingLayer;
		nums.push_back(sprite);
		iterator++;
	}
}

int Number::getFullWidth()
{
	if (nums.size() == 0)
		return (0);
	int offset = rounding((float)nums[0]->dest.w + (float)nums[0]->dest.w * 0.1f);
	return (offset * (int)nums.size());
}

void Number::AlphaMod(Uint8 alpha)
{
	for (int i = 0; i < nums.size(); i++)
	{
		nums[i]->AlphaMod(alpha);
	}
}

void Number::ColorMod(Uint8 r, Uint8 g, Uint8 b)
{
	for (int i = 0; i < nums.size(); i++)
	{
		nums[i]->ColorMod(r, g, b);
	}
}

void Number::Activate()
{
	for (int i = 0; i < nums.size(); i++)
	{
		nums[i]->Activate();
	}
}

void Number::Deactivate()
{
	for (int i = 0; i < nums.size(); i++)
	{
		nums[i]->Deactivate();
	}
}

void Number::Position(Vector place)
{
	if (nums.size() == 0)
		return ;
	int offset = rounding((float)nums[0]->dest.w + (float)nums[0]->dest.w * 0.1f);
	for (int i = 0; i < nums.size(); i++)
	{
		Vector pos(place.x + (float)(offset * i), place.y);
		nums[i]->Position(pos);
	}
}

void Number::Move(Vector amount)
{
	for (int i = 0; i < nums.size(); i++)
		nums[i]->Move(amount);
}

void Number::Resize(int size)
{
	if (nums.size() == 0)
		return ;
	int ogOffset = rounding((float)nums[0]->dest.w + (float)nums[0]->dest.w * 0.1f);
	int newOffset = rounding((float)size + (float)size * 0.1f);
	int diff = newOffset - ogOffset;
	for (int i = 0; i < nums.size(); i++)
	{
		nums[i]->dest.x += diff * i;
		nums[i]->dest.w = size;
		nums[i]->dest.h = size;
	}
}

void Number::Destroy()
{
	for (int i = 0; i < nums.size(); i++)
		delete nums[i];
	nums.clear();
}
