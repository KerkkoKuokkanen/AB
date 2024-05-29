
#include "../../../hdr/ow/tools/owCameraHandler.h"
#include "../../../hdr/render/camera.h"

void OwCameraHandler::SetBaseMove(SDL_Point start, SDL_Point end, int time)
{
	baseMover.start = start;
	baseMover.end = end;
	baseMover.time = 0;
	baseMover.goalTime = time;
	baseMover.active = true;
	gameCamera.x = start.x;
	gameCamera.y = start.y;
	float x = (float)(end.x - start.x);
	float y = (float)(end.y - start.y);
	x /= (float)time;
	y /= (float)time;
	baseMover.dirUnit = {x, y};
}

void OwCameraHandler::HandleDefault()
{
	SDL_Point pos = GetBGPosition();
	SDL_Point startPosition = {pos.x * 3200 + 3200 / 2, pos.y * 3200 + 3200 / 2};
	gameCamera.x = startPosition.x;
	gameCamera.y = startPosition.y;
}

void OwCameraHandler::UpdateBaseMover()
{
	baseMover.time++;
	SDL_FPoint start = {(float)baseMover.start.x, (float)baseMover.start.y};
	SDL_FPoint curr = {	start.x + baseMover.dirUnit.x * (float)baseMover.time,
						start.y + baseMover.dirUnit.y * (float)baseMover.time};
	gameCamera.x = (int)curr.x;
	gameCamera.y = (int)curr.y;
	if (baseMover.time == baseMover.goalTime)
		baseMover.active = false;
}

void OwCameraHandler::Update()
{
	if (baseMover.active == false)
	{
		HandleDefault();
		return ;
	}
	UpdateBaseMover();
}

void OwCameraHandler::Destroy()
{

}
