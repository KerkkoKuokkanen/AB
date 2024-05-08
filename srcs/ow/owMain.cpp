
#include "../../hdr/ow/owHeader.h"
#include "../../hdr/ow/owKeys.h"
#include "../../hdr/ow/tiles/tileDataHolder.h"

void MovePosition(TileDataHolder *holder)
{
	if (owKeys.click == RELEASE_CLICK)
	{
		int x = rand() % 20;
		int y = rand() % 20;
		holder->SetPosition({x, y});
	}
}

void OverWorldLoop()
{
	clock_t start, end;
	int fakeX = 0, fakeY = 0;
	InitOwLoop();
	TileDataHolder *dataHolder = new TileDataHolder(NULL);
	while (true)
	{
		start = clock();
		eventPoller(owKeys, fakeX, fakeY);
		OwManageMouseClick(owKeys);
		MovePosition(dataHolder);
		dataHolder->Update();
		owState.renderer->RenderAll();
		end = clock();
		SDL_Delay(ow_figure_the_delay(start, end));
	}
	delete dataHolder;
}
