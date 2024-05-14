
#include "../../../hdr/ow/tools/cameraMover.h"
#include "../../../hdr/tools/vector.h"
# include "../../../hdr/render/camera.h"

void CameraMover::SetCameraMove(SDL_Point start, SDL_Point end, int amount)
{
	travelPoints.clear();
	iterator = 0;
	SDL_FPoint starter = {(float)start.x, (float)start.y};
	Vector magVec((float)(end.x - start.x), (float)(end.y - start.y));
	for (int i = 0; i < amount; i++)
	{
		float unit = 1.0f - ((float)i / (float)amount);
		float multi = 1.0f - (unit * unit * unit);
		SDL_FPoint pos = starter;
		pos.x += magVec.x * multi;
		pos.y += magVec.y * multi;
		SDL_Point add = {(int)pos.x, (int)pos.y};
		travelPoints.push_back(add);
	}
	travelPoints.push_back(end);
}

void CameraMover::Update()
{
	if (travelPoints.size() == 0)
		return ;
	if (iterator >= travelPoints.size())
	{
		travelPoints.clear();
		iterator = 0;
		return ;
	}
	SDL_Point current = travelPoints[iterator];
	gameCamera.x = current.x;
	gameCamera.y = current.y;
	iterator++;
}

void CameraMover::ClearCameraMove()
{
	travelPoints.clear();
	iterator = 0;
}
