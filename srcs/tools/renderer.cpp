
#include "../../hdr/ab.h"
#include "../../hdr/classes/renderer.h"
#include "../../hdr/global.h"

bool compareObjects(const Sprite *obj1, const Sprite *obj2) {
	if (std::abs(obj1->dest.y - obj2->dest.y) < 0.01f)
		return obj1->dest.x < obj2->dest.x;
	else
		return obj1->dest.y > obj2->dest.y;
}

bool layerSorted(std::vector<int> &sortedLayers, int layer)
{
	for (int i = 0; i < sortedLayers.size(); i++)
	{
		if (layer == sortedLayers[i])
			return (true);
	}
	return (false);
}

void Renderer::RenderAll()
{
	SDL_RenderClear(rend);
	for (int i = 0; i < spriteLayers.size(); i++)
	{
		if (layerSorted(ySortedLayers, i))
			std::sort(spriteLayers[i].begin(), spriteLayers[i].end(), compareObjects);
		for (int j = 0; j < spriteLayers[i].size(); j++)
			spriteLayers[i][j]->Render(rend);
	}
	SDL_RenderPresent(rend);
}

void Renderer::Render()
{
	for (int i = 0; i < spriteLayers.size(); i++)
	{
		if (layerSorted(ySortedLayers, i))
			std::sort(spriteLayers[i].begin(), spriteLayers[i].end(), compareObjects);
		for (int j = 0; j < spriteLayers[i].size(); j++)
			spriteLayers[i][j]->Render(rend);
	}
}

Sprite::~Sprite()
{
	if (spritesLayer == -1)
		return ;
	gameState.render->RemoveSprite(this, spritesLayer);
}

void Sprite::RemoveFromRenderer()
{
	if (spritesLayer == -1)
		return ;
	gameState.render->RemoveSprite(this, spritesLayer);
}
