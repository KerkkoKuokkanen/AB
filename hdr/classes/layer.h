
#ifndef LAYER_H
# define LAYER_H

# include "../ab.h"
# include <algorithm>

bool spriteComparator(Sprite* sprite1, Sprite* sprite2) {
	if (sprite1->dest.y == sprite2->dest.y) {
		return sprite1->dest.x < sprite2->dest.x;
	}
	return sprite1->dest.y < sprite2->dest.y;
};

class Layer
{
	private:
		SDL_Renderer *rend;
		bool ySorted = false;
		std::vector<Sprite*> sprites;
		int layerNumber = 0;
	public:
		Layer(SDL_Renderer *rend, bool ySorted, int layerNumber) {
			Layer::rend = rend;
			Layer:: ySorted = ySorted;
			Layer::layerNumber = layerNumber;
		};
		void addSprite(Sprite *sprite) {
			Layer::sprites.push_back(sprite);
		};
		void changeLayerNumber(int layerNumber) {
			Layer::layerNumber = layerNumber;
		};
		void renderLayer() {
			if (!ySorted)
			{
				for (int i = 0; i < sprites.size(); i++)
					sprites[i]->Render(rend);
				return ;
			}
			std::sort(sprites.begin(), sprites.end(), spriteComparator);
			for (int i = 0; i < sprites.size(); i++)
				sprites[i]->Render(rend);
		};
};

#endif

