
#ifndef OW_CAMERA_HANDLER_H
# define OW_CAMERA_HANDLER_H

# include "../../../SDL2/SDL.h"
# include <vector>

typedef struct s_BaseMover
{
	SDL_Point start;
	SDL_Point end;
	SDL_FPoint dirUnit;
	int goalTime;
	int time;
	bool active;
}				t_BaseMover;

class OwCameraHandler
{
	private:
		t_BaseMover baseMover = {{0, 0}, {0, 0}, {0.0f, 0.0f}, 0, 0, false};
		void HandleDefault();
		void UpdateBaseMover();
	public:
		~OwCameraHandler() {Destroy();};
		void SetBaseMove(SDL_Point start, SDL_Point end, int time);
		void Update();
		void Destroy();
};

SDL_Point GetBGPosition();

#endif
