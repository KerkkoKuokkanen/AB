
#include "../../../hdr/ow/owHeader.h"
#include "../../../hdr/ow/owKeys.h"
#include "../../../hdr/ow/tiles/tileDataHolder.h"

TileDataHolder *holder = NULL;

void SetTheHolder(TileDataHolder *hold)
{
	holder = hold;
}

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

bool SetBGPosition(int x, int y, int time)
{
	if (holder == NULL)
		return (false);
	bool ret = holder->SetPosition({x, y}, time);
	return (ret);
}

SDL_Point GetBGPosition()
{
	SDL_Point pos = {0, 0};
	if (holder == NULL)
		return (pos);
	pos = holder->GetPosition();
	return (pos);
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
