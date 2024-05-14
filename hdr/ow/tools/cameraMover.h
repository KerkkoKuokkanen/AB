
#ifndef CAMERA_MOVER_H
# define CAMERA_MOVER_H

# include "../../../SDL2/SDL.h"
# include <vector>

class CameraMover
{
	private:
		std::vector<SDL_Point> travelPoints = {};
		int iterator = 0;
	public:
		void SetCameraMove(SDL_Point start, SDL_Point end, int amount);
		void Update();
		void ClearCameraMove();
};

#endif
