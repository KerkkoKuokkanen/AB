
#include "../../hdr/ow/owHeader.h"
#include "../../hdr/ow/owKeys.h"
#include "../../hdr/ow/tiles/tileDataHolder.h"

static void ClearOW(TileDataHolder *holder)
{
	delete holder;
	gameCamera.camMover.ClearCameraMove();
	owState.renderer->RemoveAll();
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
		dataHolder->Update();
		gameCamera.camMover.Update();
		owState.renderer->RenderAll();
		end = clock();
		SDL_Delay(ow_figure_the_delay(start, end));
	}
	ClearOW(dataHolder);
}
