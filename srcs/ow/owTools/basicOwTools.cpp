
#include "../../../hdr/ow/owHeader.h"
#include "../../../hdr/ow/owKeys.h"
#include "../../../hdr/ow/tiles/tileDataHolder.h"

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
	gameCamera.screen.unit = 1.0f / 100000.0f;
	gameCamera.screen.xPixelUnit = (1.0f / gameCamera.screen.unit) / gameCamera.screen.width;
	gameCamera.screen.yPixelUnit = (1.0f / gameCamera.screen.unit) / gameCamera.screen.height;
	owState.renderer->CreateLayer(LAYER_ORDER_SORT); //Tile Layer
	InitOwUpdates();
}

void OwPrintStat()
{
	static int i = 0;
	printf("%d\n", i);
	i++;
}

void OwManageMouseClick(t_Keys &keys)
{
	static int clickState = 0;
	if (clickState == 0 && keys.click == INITIAL_CLICK)
	{
		clickState = 1;
		return ;
	}
	if (clickState == 1 && keys.click == INITIAL_CLICK)
	{
		keys.click = HOLD_CLICK;
		return ;
	}
	if (clickState == 1 && keys.click == NO_CLICK)
	{
		clickState = 2;
		keys.click = RELEASE_CLICK;
		return ;
	}
	if (clickState == 2)
	{
		keys.click = NO_CLICK;
		clickState = 0;
	}
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
