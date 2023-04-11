
#ifndef RENDERER_H
# define RENDERER_H

# include "../ab.h"

class Renderer
{
	private:
		SDL_Renderer *rend;
		std::vector<std::vector<Sprite*>> spriteLayers;
		std::vector<int> ySortedLayers;
	public:
		Renderer(SDL_Renderer *rend) { Renderer::rend = rend; };
		int CreateLayer(bool ySorted) {
			std::vector<Sprite*> add;
			spriteLayers.push_back(add);
			int index = spriteLayers.size() - 1;
			if (ySorted)
				ySortedLayers.push_back(index);
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
