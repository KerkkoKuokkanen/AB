
#include "../../../hdr/global.h"
#define DIFFERENCE 500

Vector Markers::GetMarkerStartPlace(SDL_Point position)
{
	Character *character = gameState.battle.ground->map[position.y][position.x].character;
	SDL_Surface *sur = getSurface(character);
	Uint32 *pixels = (Uint32*)sur->pixels;
	float x = character->sprite->dest.x + (character->sprite->dest.w / 2);
	int yStop = 0;
	bool broke = false;
	for (int i = 0; i < sur->h; i++)
	{
		for (int j = 0; j < sur->w; j++)
		{
			if (pixels[(i * sur->w) + j] == 0)
				continue ;
			broke = true;
			yStop = i;
			break ;
		}
		if (broke)
			break ;
	}
	if (!broke)
		return (Vector(x, (float)character->sprite->dest.y));
	float hUnit = (float)character->sprite->dest.h / (float)sur->h;
	float y = (float)character->sprite->dest.y + (hUnit * (float)yStop);
	y -= 750.0f;
	return (Vector(x, y));
}

int Markers::GetMarkerPosition(SDL_Point position)
{
	if (marked.size() == 0)
		return (-1);
	for (int i = 0; i < marked.size(); i++)
	{
		if (marked[i].pos.x == position.x && marked[i].pos.y == position.y)
			return (i);
	}
	return (-1);
}

void Markers::MultipleMarkers(t_MarkerPlace *mark)
{
	Vector place = GetMarkerStartPlace(mark->pos);
	place.y = (float)mark->sprites[0]->dest.y;
	SDL_Rect dest = {(int)place.x, (int)place.y, 400, 400};
	Sprite *sprite = new Sprite(gameState.textures.marker, dest, NULL, NULL, 0, FLIP_NONE);
	Uint8 r = colors[mark->colorSign].r;
	Uint8 g = colors[mark->colorSign].g;
	Uint8 b = colors[mark->colorSign].b;
	sprite->ColorMod(r, g, b);
	gameState.render->AddSprite(sprite, INFO_LAYER);
	mark->sprites.push_back(sprite);
	int amount = mark->sprites.size();
	int start = (int)place.x - ((DIFFERENCE * amount) / 2);
	for (int i = 0; i < amount; i++)
	{
		int x = start + (DIFFERENCE * i);
		mark->sprites[i]->Position(Vector((float)(x - 200), place.y));
	}
}

void Markers::SetColor(t_MarkerPlace *mark)
{
	if (first)
	{
		first = false;
		colorCounter = rand() % 4;
	}
	Uint8 r = colors[colorCounter].r;
	Uint8 g = colors[colorCounter].g;
	Uint8 b = colors[colorCounter].b;
	mark->sprites[0]->ColorMod(r, g, b);
	mark->colorSign = colorCounter;
	colorCounter++;
	if (colorCounter >= 4)
		colorCounter = 0;
}

int Markers::GetMarkersForPoint(SDL_Point pos)
{
	int amount = 0;
	for (int i = 0; i < marked.size(); i++)
	{
		if (marked[i].pos.x == pos.x && marked[i].pos.y == pos.y)
		{
			amount = marked[i].sprites.size();
			break ;
		}
	}
	return (amount);
}

void Markers::PlaceMarker(SDL_Point position)
{
	if (gameState.battle.ground->map[position.y][position.x].character == NULL)
		return ;
	PlaySound(gameState.audio.select, Channels::SELECT, 0);
	int index = GetMarkerPosition(position);
	if (index != (-1))
	{
		MultipleMarkers(&marked[index]);
		return ;
	}
	Vector place = GetMarkerStartPlace(position);
	t_MarkerPlace add;
	add.pos = position;
	SDL_Rect dest = {(int)(place.x - 200.0f), (int)place.y, 400, 400};
	Sprite *sprite = new Sprite(gameState.textures.marker, dest, NULL, NULL, 0, FLIP_NONE);
	gameState.render->AddSprite(sprite, INFO_LAYER);
	add.sprites.push_back(sprite);
	SetColor(&add);
	marked.push_back(add);
}

void Markers::Destroy()
{
	for (int i = 0; i < marked.size(); i++)
	{
		for (int j = 0; j < marked[i].sprites.size(); j++)
		{
			delete marked[i].sprites[j];
		}
		marked[i].sprites.clear();
	}
	marked.clear();
}
