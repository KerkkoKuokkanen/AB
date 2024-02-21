
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

void TextBubble::SetMouseFollow(SDL_Point followPos)
{
	TextBubble::followPos = followPos;
	followMouse = true;
}

void TextBubble::Update()
{
	if (followMouse == false)
		return ;
	int x = gameState.keys.smX;
	int y = gameState.keys.smY;
	x += followPos.x;
	y += followPos.y;
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
