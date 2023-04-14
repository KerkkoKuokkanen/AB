
#include "../../hdr/ab.h"
#include "../../hdr/global.h"

SDL_Texture	*get_texture(SDL_Renderer *rend, const char *filePath)
{
	SDL_Surface	*surface = IMG_Load(filePath);
	SDL_Texture *text = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	SDL_SetTextureScaleMode(text, SDL_ScaleModeLinear);
	return (text);
}

int	rounding(float value)
{
	int val = static_cast<int>(value);
	float tester = value - val;
	if (tester >= 0.5f)
		return (val + 1);
	return (val);
}

SDL_FRect	translateSprite(SDL_Rect dest, bool staticSprite)
{
	int cx = 0;
	int cy = 0;
	float w = (float)gameState.screen.width;
	float h = (float)gameState.screen.height;
	if (!staticSprite)
	{
		cx = gameState.camera.x;
		cy = gameState.camera.y;
	}
	SDL_FRect ret = {
		(float)(dest.x - cx) / gameState.screen.xPixelUnit + gameState.screen.midPointX,
		(float)(dest.y - cy) / gameState.screen.yPixelUnit * gameState.screen.aspectRatio + gameState.screen.midPointY,
		(float)dest.w / gameState.screen.xPixelUnit,
		(float)dest.h / gameState.screen.yPixelUnit * gameState.screen.aspectRatio
	};
	return (ret);
}

int	figure_the_delay(clock_t start, clock_t end)
{
	double	time;
	int		ret;

	time = 0.0;
	time += (double)(end - start) / CLOCKS_PER_SEC;
	ret = FRAME - (int)(time * 1000);
	if (ret < 0)
		return (0);
	else
		return (ret);
}
