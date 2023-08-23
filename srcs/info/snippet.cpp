
#include "../../hdr/global.h"

void Snippet::SetOutlineAmount(int amount)
{
	if (outline[0] == NULL)
		return ;
	SDL_Rect dest = sprite->dest;
	outline[0]->dest = {dest.x - amount, dest.y - amount, dest.w, dest.h};
	outline[1]->dest = {dest.x + amount, dest.y - amount, dest.w, dest.h};
	outline[2]->dest = {dest.x - amount, dest.y + amount, dest.w, dest.h};
	outline[3]->dest = {dest.x + amount, dest.y + amount, dest.w, dest.h};
}

void Snippet::SetScaled(bool scaled)
{
	sprite->setScaled(scaled);
	if (outlineBool)
	{
		outline[0]->setScaled(scaled);
		outline[1]->setScaled(scaled);
		outline[2]->setScaled(scaled);
		outline[3]->setScaled(scaled);
	}
}

void Snippet::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	sprite->ColorMod(r, g, b);
}

void Snippet::SetOutlineColor(Uint8 r, Uint8 g, Uint8 b)
{
	outline[0]->ColorMod(r, g, b);
	outline[1]->ColorMod(r, g, b);
	outline[2]->ColorMod(r, g, b);
	outline[3]->ColorMod(r, g, b);
}

void Snippet::CreateOutline(SDL_Rect dest, int layer, bool staticSprite)
{
	dest.x -= 100;
	dest.y -= 100;
	outline[0] = new Sprite(text, dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
	outline[0]->ColorMod(1, 1, 1);
	gameState.render->AddSprite(outline[0], layer);
	dest.x += 200;
	outline[1] = new Sprite(text, dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
	outline[1]->ColorMod(1, 1, 1);
	gameState.render->AddSprite(outline[1], layer);
	dest.x -= 200;
	dest.y += 200;
	outline[2] = new Sprite(text, dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
	outline[2]->ColorMod(1, 1, 1);
	gameState.render->AddSprite(outline[2], layer);
	dest.x += 200;
	outline[3] = new Sprite(text, dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
	outline[3]->ColorMod(1, 1, 1);
	gameState.render->AddSprite(outline[3], layer);
}

void Snippet::SetAlphaMod(Uint8 alpha)
{
	sprite->AlphaMod(alpha);
	if (outlineBool)
	{
		outline[0]->AlphaMod(alpha);
		outline[1]->AlphaMod(alpha);
		outline[2]->AlphaMod(alpha);
		outline[3]->AlphaMod(alpha);
	}
}

void Snippet::ClearAlphaMod()
{
	sprite->ClearAlphaMod();
	if (outlineBool)
	{
		outline[0]->ClearAlphaMod();
		outline[1]->ClearAlphaMod();
		outline[2]->ClearAlphaMod();
		outline[3]->ClearAlphaMod();
	}
}

void Snippet::Move(Vector amount)
{
	sprite->Move(amount);
	if (outlineBool)
	{
		outline[0]->Move(amount);
		outline[1]->Move(amount);
		outline[2]->Move(amount);
		outline[3]->Move(amount);
		SetOutlineAmount(Snippet::amount);
	}
}

void Snippet::Position(SDL_Point pos)
{
	sprite->dest.x = pos.x;
	sprite->dest.y = pos.y;
	SetOutlineAmount(amount);
}

void Snippet::SetOrderLayer(int order)
{
	sprite->orderLayer = order;
	if (outlineBool)
	{
		outline[0]->orderLayer = order - 1;
		outline[1]->orderLayer = order - 1;
		outline[2]->orderLayer = order - 1;
		outline[3]->orderLayer = order - 1;
	}
}

Snippet::Snippet(const char *text, int fontType, bool outline, SDL_Point pos, int size, int offset, int layer, bool staticSprite)
{
	Snippet::outlineBool = outline;
	Snippet::text = get_text(text, fontType);
	std::string used(text);
	int len = used.length();
	SDL_Rect dest = {pos.x, pos.y, len * offset, size};
	sprite = new Sprite(Snippet::text, dest, NULL, NULL, 0, FLIP_NONE, staticSprite);
	sprite->orderLayer = 1;
	gameState.render->AddSprite(sprite, layer);
	if (outline)
		CreateOutline(dest, layer, staticSprite);
}

void Snippet::Destroy()
{
	SDL_DestroyTexture(text);
	delete sprite;
	for (int i = 0; i < 4; i++)
	{
		if (outline[i] != NULL)
			delete outline[i];
	}
}
