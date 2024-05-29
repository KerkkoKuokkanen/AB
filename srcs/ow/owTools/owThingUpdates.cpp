
#include "../../../hdr/ow/tools/owCameraHandler.h"
#include "../../../hdr/ow/tiles/tileDataHolder.h"

TileDataHolder *holder = NULL;
OwCameraHandler *camHandler = NULL;

void InitOwUpdates()
{
	holder = new TileDataHolder(NULL);
	camHandler = new OwCameraHandler;
}

TileDataHolder *GetReferenceToTileDataHolder()
{
	return (holder);
}

OwCameraHandler *GetReferenceToCamHandler()
{
	return (camHandler);
}

void ClearOwUpdates()
{
	if (holder != NULL)
		delete holder;
	if (camHandler != NULL)
		delete camHandler;
	holder = NULL;
	camHandler = NULL;
}

void OwUpdates()
{
	holder->Update();
	camHandler->Update();
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
