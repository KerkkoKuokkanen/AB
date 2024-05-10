
#ifndef CAMERA_H
# define CAMERA_H

# include "../ow/tools/cameraMover.h"

typedef struct s_Screen
{
	int width, height;
	float unit;
	float aspectRatio;
	int midPointX, midPointY;
	float xPixelUnit, yPixelUnit;
	float xStaticUnit, yStaticUnit;
}				t_Screen;

typedef struct	s_ScreenShake
{
	int xShake;
	int yShake;
	int shakeCounter;
	int shakeVolume;
}				t_ScreenShake;

typedef struct s_Camera
{
	int x, y;
	float zoom;
	int clickTimePosX, clickTimePosY;
	t_ScreenShake screenShake;
	t_Screen screen;
	CameraMover camMover;
}				t_Camera;

extern t_Camera gameCamera;

#endif
