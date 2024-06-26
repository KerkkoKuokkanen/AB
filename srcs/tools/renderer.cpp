
#include "../../hdr/global.h"

bool compareObjects(const Sprite *obj1, const Sprite *obj2) {
	if (obj1->orderLayer < obj2->orderLayer)
		return true;
	else if (obj1->orderLayer > obj2->orderLayer)
		return false;
	if (std::abs(obj1->dest.y - obj2->dest.y) < 0.01f)
		return obj1->dest.x < obj2->dest.x;
	else
		return obj1->dest.y > obj2->dest.y;
}

bool compareObjectsReverse(const Sprite *obj1, const Sprite *obj2) {
	if (obj1->orderLayer < obj2->orderLayer)
		return true;
	else if (obj1->orderLayer > obj2->orderLayer)
		return false;
	if (std::abs(obj1->dest.y - obj2->dest.y) < 0.01f)
		return obj1->dest.x > obj2->dest.x;
	else
		return obj1->dest.y < obj2->dest.y;
}

bool compareObjectsDepth(const Sprite *obj1, const Sprite *obj2) {
	if (obj1->orderLayer < obj2->orderLayer)
		return true;
	else if (obj1->orderLayer > obj2->orderLayer)
		return false;
	return (obj1->z < obj2->z);
}

bool compareObjectsOrder(const Sprite *obj1, const Sprite *obj2) {
	if (obj1->orderLayer < obj2->orderLayer)
		return true;
	return false;
}

int layerSorted(std::vector<t_Sort> &sortedLayers, int layer)
{
	for (int i = 0; i < sortedLayers.size(); i++)
	{
		if (layer == sortedLayers[i].layer)
			return (sortedLayers[i].sortType);
	}
	return (0);
}

Renderer::Renderer(SDL_Renderer *rend)
{
	Renderer::rend = rend;
}

void Renderer::RenderAll()
{
	SDL_RenderClear(rend);
	Render();
	SDL_RenderPresent(rend);
}

void Renderer::RemoveAll()
{
	for (int i = 0; i < spriteLayers.size(); i++)
		spriteLayers[i].clear();
	spriteLayers.clear();
}

void Renderer::Render()
{
	for (int i = 0; i < spriteLayers.size(); i++)
	{
		int sort = layerSorted(sortedLayers, i);
		if (sort != 0)
		{
			if (sort == LAYER_YSORT)
				std::sort(spriteLayers[i].begin(), spriteLayers[i].end(), compareObjects);
			else if (sort == LAYER_REVERSE_YSORT)
				std::sort(spriteLayers[i].begin(), spriteLayers[i].end(), compareObjectsReverse);
			else if (sort == LAYER_DEPTH_SORT)
				std::sort(spriteLayers[i].begin(), spriteLayers[i].end(), compareObjectsDepth);
			else if (sort == LAYER_ORDER_SORT)
				std::sort(spriteLayers[i].begin(), spriteLayers[i].end(), compareObjectsOrder);
		}
		for (int j = 0; j < spriteLayers[i].size(); j++)
			spriteLayers[i][j]->Render(rend);
	}
}

Sprite::~Sprite()
{
	if (spritesLayer == -1)
		return ;
	if (!removed)
		gameState.render->RemoveSprite(this, spritesLayer);
	if (deleteTexture && sprite != NULL)
		SDL_DestroyTexture(sprite);
}

void Sprite::Render(SDL_Renderer *rend)
{
	if (!active)
		return ;
	SDL_FRect rect;
	if (translated)
	{
		if (!staticSprite)
		{
			if (scaled)
				rect = translateSprite(dest);
			else
				rect = translateSpriteWithoutScale(dest);
		}
		else
			rect = staitcTranslateSprite(dest);
	}
	else
		rect = {(float)dest.x, (float)dest.y, (float)dest.w, (float)dest.h};
	bool tt = false;
	if (alpha != 255)
	{
		tt = true;
		SDL_SetTextureAlphaMod(sprite, alpha);
	}
	bool col = false;
	if (red != 0 || blue != 0 || green != 0)
	{
		col = true;
		SDL_SetTextureColorMod(sprite, red, green, blue);
	}
	SDL_RenderCopyExF(rend, sprite, srect, &rect, angle, point, flip);
	if (tt)
		SDL_SetTextureAlphaMod(sprite, 255);
	if (col)
		SDL_SetTextureColorMod(sprite, 255, 255, 255);
};

void Sprite::RemoveFromRenderer()
{
	if (spritesLayer == -1)
		return ;
	gameState.render->RemoveSprite(this, spritesLayer);
}
