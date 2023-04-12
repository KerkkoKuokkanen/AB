
#include "../../hdr/ab.h"
#include "../../hdr/global.h"

SDL_Texture	*get_texture(SDL_Renderer *rend, const char *filePath)
{
	SDL_Surface	*surface = IMG_Load(filePath);
	SDL_Texture *text = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
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

SDL_Rect	translateSprite(SDL_Rect dest, bool staticSprite)
{
	float cx = 0.0f;
	float cy = 0.0f;
	float w = (float)gameState.screen.width, h = (float)gameState.screen.height;
	if (!staticSprite)
	{
		cx = gameState.camera.x;
		cy = gameState.camera.y;
	}
	float xPos = (gameState.screen.unit * ((float)dest.x - cx) * w) + gameState.screen.midPointX;
	float yPos = (gameState.screen.unit * ((float)dest.y - cy) * h) + gameState.screen.midPointY;
	float width = gameState.screen.unit* (float)dest.w * w;
	float height = gameState.screen.unit * (float)dest.h * h * gameState.screen.aspectRatio;

	SDL_Rect ret;
	ret.x = rounding(xPos);
	ret.y = rounding(yPos);
	ret.w = rounding(width);
	ret.h = rounding(height);
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
