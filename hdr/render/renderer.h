
#ifndef RENDERER_H
# define RENDERER_H

# include <vector>
# include "sprite.h"

typedef struct s_Sort
{
	int layer;
	int sortType;
}				t_Sort;

class Renderer
{
	private:
		SDL_Renderer *rend;
		std::vector<std::vector<Sprite*>> spriteLayers;
		std::vector<t_Sort> sortedLayers;
	public:
		Renderer(SDL_Renderer *rend);
		int CreateLayer(int sortType) {
			std::vector<Sprite*> add;
			spriteLayers.push_back(add);
			int index = spriteLayers.size() - 1;
			if (sortType == LAYER_YSORT || sortType == LAYER_REVERSE_YSORT || sortType == LAYER_DEPTH_SORT || sortType == LAYER_ORDER_SORT)
			{
				t_Sort s = {index, sortType};
				sortedLayers.push_back(s);
			}
			return (index);
		};
		bool AddSprite(Sprite *sprite, int layerNumber) {
			if (layerNumber < 0 || layerNumber >= spriteLayers.size())
			{
				printf("renderer.h, Add: no layer exist for sprite\n");
				return (false);
			}
			spriteLayers[layerNumber].push_back(sprite);
			sprite->spritesLayer = layerNumber;
			return (true);
		};
		bool RemoveSprite(Sprite *sprite, int layerNumber) {
			if (layerNumber < 0 || layerNumber >= spriteLayers.size())
			{
				printf("renderer.h, Remove: no layer exist for sprite\n");
				return (false);
			}
			auto it = std::find(spriteLayers[layerNumber].begin(), spriteLayers[layerNumber].end(), sprite);
			if (it != spriteLayers[layerNumber].end())
			{
				spriteLayers[layerNumber].erase(it);
				return (true);
			}
			printf("render.h :could not find the sprite\n");
			return (false);
		}
		void ClearLayer(int layer)
		{
			spriteLayers[layer].clear();
		}
		void RemoveRenderLayer(int layer)
		{
			int size = spriteLayers.size();
			if (layer < 0 || layer >= size)
				return ;
			spriteLayers[layer].clear();
			spriteLayers.erase(spriteLayers.begin() + layer);
		}
		void RemoveAll()
		{
			for (int i = 0; i < spriteLayers.size(); i++)
				spriteLayers[i].clear();
			spriteLayers.clear();
		}
		void RenderClear() {
			SDL_RenderClear(rend);
		};
		void RenderSwap() {
			SDL_RenderPresent(rend);
		}
		void Render();
		void RenderAll();
};

#endif
