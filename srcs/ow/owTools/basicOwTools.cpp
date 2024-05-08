
#include "../../../hdr/ow/owHeader.h"

int	ow_figure_the_delay(clock_t start, clock_t end)
{
	double	time;
	int		ret;
	time = 0.0;
	time += (double)(end - start) / CLOCKS_PER_SEC;
	ret = FRAME - (int)(time * 1000.0f);
	if (ret < 0)
		return (0);
	else
		return (ret);
}

void InitOwLoop()
{
	owState.renderer->CreateLayer(LAYER_ORDER_SORT); //Tile Layer
}

void OwPrintStat()
{
	static int i = 0;
	printf("%d\n", i);
	i++;
}

SDL_Texture *GetCorrespondingTileText(int type)
{
	switch (type)
	{
		case TileTextureTypes::GRASS_TILE:
			return (owState.textures.tileTexts.grassTile);
	}
	return (owState.textures.tileTexts.grassTile);
}
