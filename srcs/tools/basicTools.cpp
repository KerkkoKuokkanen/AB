
#include "../../hdr/ab.h"

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

SDL_Rect	translateSprite(SDL_Rect dest)
{
	dest.x -= gameState.camera.x;
	dest.y -= gameState.camera.y;
	float xPos = gameState.screen.unit * (float)dest.x * gameState.screen.width;
	float yPos = gameState.screen.unit * (float)dest.y * gameState.screen.height;
	float width = gameState.screen.unit * (float)dest.w * gameState.screen.width;
	float height = gameState.screen.unit * (float)dest.h * gameState.screen.height * gameState.screen.aspectRatio;

	SDL_Rect ret;
	ret.x = rounding(xPos);
	ret.y = rounding(yPos);
	ret.w = rounding(width);
	ret.h = rounding(height);
	return (ret);
}

void	init(t_wr *wr)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(26);
	SDL_CreateWindowAndRenderer(1280, 720, 0, &wr->win, &wr->rend);
	SDL_SetRenderDrawBlendMode(wr->rend, SDL_BLENDMODE_BLEND);
	gameState.screen.width = 1280;
	gameState.screen.height = 720;
	gameState.screen.aspectRatio = (float)gameState.screen.width / (float)gameState.screen.height;
	gameState.screen.unit = 1.0f / 10000.0f;
	gameState.camera.x = 0;
	gameState.camera.y = 0;
	gameState.camera.zoom = 0.0f;
	gameState.keys.w = 0;
	gameState.keys.a = 0;
	gameState.keys.s = 0;
	gameState.keys.d = 0;
	gameState.keys.click = 0;
	//SDL_SetWindowFullscreen(wre->win, window_check_value);
	//SDL_ShowCursor(SDL_DISABLE);
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
