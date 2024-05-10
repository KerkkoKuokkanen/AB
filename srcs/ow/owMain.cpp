
#include "../../hdr/ow/owHeader.h"
#include "../../hdr/ow/owKeys.h"
#include "../../hdr/ow/tiles/tileDataHolder.h"
#define DELAY 8

void MovePosition(TileDataHolder *holder)
{
	static int delay = 0;
	int horz = owKeys.right - owKeys.left;
	int updwm = owKeys.down - owKeys.up;
	if (horz != 0 && delay == 0)
	{
		SDL_Point pos = holder->GetPosition();
		pos.x += horz;
		holder->SetPosition(pos);
		delay = DELAY;
	}
	else if (updwm != 0 && delay == 0)
	{
		SDL_Point pos = holder->GetPosition();
		pos.y += updwm;
		holder->SetPosition(pos);
		delay = DELAY;
	}
	if (owKeys.right == 0 && owKeys.left == 0 && owKeys.up == 0 && owKeys.down == 0)
		delay = 0;
	if (delay > 0)
		delay--;
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
		gameCamera.camMover.Update();
		owState.renderer->RenderAll();
		end = clock();
		SDL_Delay(ow_figure_the_delay(start, end));
	}
	delete dataHolder;
}
