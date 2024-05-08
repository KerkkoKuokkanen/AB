
#include "../../../hdr/ow/tiles/mapTile.h"
#include "../../../hdr/ow/owHeader.h"

MapTile::MapTile(SDL_Texture *texture, SDL_Rect sRect, SDL_Point pos)
{
	SDL_Rect dest = {pos.x, pos.y, DIMENTIONS, DIMENTIONS};
	sourceRect = sRect;
	sprite = new Sprite(owState.textures.tileTexts.grassTile, dest, &sourceRect, NULL, 0, FLIP_NONE);
	outline = new Sprite(owState.textures.tileTexts.tileOutline, dest, NULL, NULL, 0, FLIP_NONE);
	outline->orderLayer = 1;
	outline->AlphaMod(60);
	outline->ColorMod(1, 1, 1);
	owState.renderer->AddSprite(sprite, TILE_LAYER);
	owState.renderer->AddSprite(outline, TILE_LAYER);
}

SDL_Point MapTile::GetDestPoint()
{
	SDL_Rect dest = sprite->dest;
	SDL_Point ret = {dest.x + dest.w / 2, dest.y + dest.h / 2};
	return (ret);
}

void MapTile::Update()
{

}

void MapTile::Destroy()
{
	if (sprite != NULL)
		delete sprite;
	if (outline != NULL)
		delete outline;
}
