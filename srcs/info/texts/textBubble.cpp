
#include "../../../hdr/global.h"

TextBubble::TextBubble(SDL_Point position)
{
	pos = position;
	SDL_Rect dest = {pos.x, pos.y, 50, 50};
	outline = new Sprite(gameState.textures.everyColor, dest, NULL, NULL, 0, FLIP_NONE, true);
	outline->AlphaMod(210);
	outline->ColorMod(54, 30, 3);
	gameState.render->AddSprite(outline, TEXT_BUBBLE_LAYER);
}

void TextBubble::ChangeOutlineColor(int r, int g, int b)
{
	outline->ColorMod(r, g, b);
}

void TextBubble::AddSnippetToBubble(Snippet *snippet, SDL_Point pos)
{
	snippet->SetOrderLayer(2);
	SDL_Point place = pos;
	place.x += pos.x;
	place.y += pos.y;
	snippet->Position(place);
	snippets.push_back({snippet, pos});
}

void TextBubble::AddSpriteToBubble(Sprite *sprite, SDL_Point pos)
{
	sprite->orderLayer = 2;
	SDL_Point place = pos;
	place.x += pos.x;
	place.y += pos.y;
	sprite->dest.x = place.x;
	sprite->dest.y = place.y;
	sprites.push_back({sprite, pos});
	gameState.render->AddSprite(sprite, TEXT_BUBBLE_LAYER);
}

void TextBubble::SetPosition(SDL_Point position)
{
	SDL_Point place = position;
	pos = place;
	outline->dest.x = place.x;
	outline->dest.y = place.y;
	for (int i = 0; i < sprites.size(); i++)
	{
		SDL_Point rePos = place;
		rePos.x += sprites[i].pos.x;
		rePos.y += sprites[i].pos.y;
		sprites[i].sprite->dest.x = rePos.x;
		sprites[i].sprite->dest.y = rePos.y;
	}
	for (int i = 0; i < snippets.size(); i++)
	{
		SDL_Point rePos = place;
		rePos.x += snippets[i].pos.x;
		rePos.y += snippets[i].pos.y;
		snippets[i].snippet->Position(rePos);
	}
}

void TextBubble::SetUpOutline(int xAdd, int yAdd)
{
	SDL_Point furthest = {0, 0};
	for (int i = 0; i < sprites.size(); i++)
	{
		int x = sprites[i].pos.x + sprites[i].sprite->dest.w;
		int y = sprites[i].pos.y + sprites[i].sprite->dest.h;
		if (x > furthest.x)
			furthest.x = x;
		if (y > furthest.y)
			furthest.y = y;
	}
	for (int i = 0; i < snippets.size(); i++)
	{
		SDL_Rect sDest = snippets[i].snippet->GetDest();
		int x = snippets[i].pos.x + sDest.w;
		int y = snippets[i].pos.y + sDest.h;
		if (x > furthest.x)
			furthest.x = x;
		if (y > furthest.y)
			furthest.y = y;
	}
	outline->dest.w = furthest.x + xAdd;
	outline->dest.h = furthest.y + yAdd;
}

void TextBubble::DisableOutline()
{
	if (outline != NULL)
		outline->Deactivate();
}

void TextBubble::SetFollowCorner(int followSign)
{
	if (followSign < 0 || followSign >= 4)
		return ;
	follorCorner = followSign;
}

void TextBubble::SetMouseFollow(SDL_Point followPos)
{
	TextBubble::followPos = followPos;
	followMouse = true;
}

int TextBubble::GetFollowX()
{
	int x = gameState.keys.smX;
	x += followPos.x;
	if (follorCorner == 0 || follorCorner == 2)
		return (x);
	x -= outline->dest.w;
	return (x);
}

int TextBubble::GetFollorY()
{
	int y = gameState.keys.smY;
	y += followPos.y;
	if (follorCorner == 0 || follorCorner == 1)
		return (y);
	float minus = (float)outline->dest.h * 1.7777f;
	y -= rounding(minus);
	return (y);
}

void TextBubble::ClearAlphaMod()
{
	for (int i = 0; i < sprites.size(); i++)
		sprites[i].sprite->ClearAlphaMod();
	for (int i = 0; i < snippets.size(); i++)
		snippets[i].snippet->ClearAlphaMod();
	outline->AlphaMod(210);
}

void TextBubble::SetAlphaMod(int alpha)
{
	if (alpha > 255)
		alpha = 255;
	if (alpha < 0)
		alpha = 0;
	for (int i = 0; i < sprites.size(); i++)
		sprites[i].sprite->AlphaMod(alpha);
	for (int i = 0; i < snippets.size(); i++)
		snippets[i].snippet->SetAlphaMod(alpha);
	float unit = 210.0f / 255.0f;
	int use = rounding(unit * (float)alpha);
	outline->AlphaMod(use);
}

void TextBubble::Update()
{
	if (followMouse == false)
		return ;
	int x = GetFollowX();
	int y = GetFollorY();
	pos = {x, y};
	for (int i = 0; i < sprites.size(); i++)
	{
		SDL_Point place = {x, y};
		place.x += sprites[i].pos.x;
		place.y += sprites[i].pos.y;
		sprites[i].sprite->dest.x = place.x;
		sprites[i].sprite->dest.y = place.y;
	}
	for (int i = 0; i < snippets.size(); i++)
	{
		SDL_Point place = {x, y};
		place.x += snippets[i].pos.x;
		place.y += snippets[i].pos.y;
		snippets[i].snippet->Position(place);
	}
	outline->dest.x = pos.x;
	outline->dest.y = pos.y;
}

void TextBubble::Destroy()
{
	for (int i = 0; i < snippets.size(); i++)
		delete snippets[i].snippet;
	for (int i = 0; i < sprites.size(); i++)
		delete sprites[i].sprite;
	if (outline != NULL)
		delete outline;
	snippets.clear();
	sprites.clear();
}
