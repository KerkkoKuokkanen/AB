
#include "../../hdr/ow/owHeader.h"
#include "../../hdr/ow/owKeys.h"
#include "../../hdr/ow/tiles/tileDataHolder.h"

static void ClearOW()
{
	ClearOwUpdates();
	owState.renderer->RemoveAll();
}

void OverWorldLoop()
{
	clock_t start, end;
	int fakeX = 0, fakeY = 0;
	InitOwLoop();
	while (true)
	{
		start = clock();
		eventPoller(owKeys, fakeX, fakeY);
		OwManageMouseClick(owKeys);
		OwUpdates();
		owState.renderer->RenderAll();
		end = clock();
		SDL_Delay(ow_figure_the_delay(start, end));
		if (owKeys.click == RELEASE_CLICK)
			break ;
	}
	ClearOW();
}
