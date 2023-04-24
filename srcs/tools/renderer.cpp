
#include "../../hdr/ab.h"
#include "../../hdr/classes/renderer.h"
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

int layerSorted(std::vector<t_Sort> &sortedLayers, int layer)
{
	for (int i = 0; i < sortedLayers.size(); i++)
	{
		if (layer == sortedLayers[i].layer)
			return (sortedLayers[i].sortType);
	}
	return (0);
}

void Renderer::RenderAll()
{
	SDL_RenderClear(rend);
	Render();
	SDL_RenderPresent(rend);
}

void Renderer::Render()
{
	for (int i = 0; i < spriteLayers.size(); i++)
	{
		if (int sort = layerSorted(sortedLayers, i) != 0)
		{
			if (sort == LAYER_YSORT)
				std::sort(spriteLayers[i].begin(), spriteLayers[i].end(), compareObjects);
			else if (sort == LAYER_REVERSE_YSORT)
				std::sort(spriteLayers[i].begin(), spriteLayers[i].end(), compareObjectsReverse);
		}
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
