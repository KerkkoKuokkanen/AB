
#include "../../hdr/ab.h"
#include "../../hdr/global.h"

void initKeys()
{
	gameState.keys.w = 0;
	gameState.keys.a = 0;
	gameState.keys.s = 0;
	gameState.keys.d = 0;
	gameState.keys.click = 0;
	gameState.keys.middleMouse = 0;
	gameState.camera.clickTimePosX = 0;
	gameState.camera.clickTimePosY = 0;
}

void initScreen(int width, int height)
{
	gameState.screen.width = width;
	gameState.screen.height = height;
	gameState.screen.aspectRatio = (float)gameState.screen.width / (float)gameState.screen.height;
	gameState.screen.midPointX = gameState.screen.width / 2;
	gameState.screen.midPointY = gameState.screen.height / 2;
	gameState.camera.x = 0;
	gameState.camera.y = 0;
	gameState.camera.zoom = 0.0f;
	float xUni = 10000.0f / (float)width;
	float yUni = 10000.0f / (float)height;
	gameState.screen.xPixelUnit = rounding(xUni);
	gameState.screen.yPixelUnit = rounding(yUni);
}

void	init(t_wr *wr)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(26);
	SDL_CreateWindowAndRenderer(1280, 720, 0, &wr->win, &wr->rend);
	SDL_SetRenderDrawBlendMode(wr->rend, SDL_BLENDMODE_BLEND);
	gameState.screen.unit = 1.0f / 10000.0f;
	initScreen(1280, 720);
	initKeys();
	static Renderer render(wr->rend);
	render.CreateLayer(true);
	gameState.render = &render;
	//SDL_SetWindowFullscreen(wre->win, window_check_value);
	//SDL_ShowCursor(SDL_DISABLE);
}
