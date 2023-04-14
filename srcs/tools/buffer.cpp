
#include "../../hdr/global.h"

//SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, screen_width, screen_height);

void Buffer::CreateBuffers(SDL_Renderer *rend)
{
	buffers[0] = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, gameState.screen.width, gameState.screen.height);
	buffers[1] = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, gameState.screen.width, gameState.screen.height);
}

void Buffer::DestroyBuffers()
{
	SDL_DestroyTexture(buffers[0]);
	SDL_DestroyTexture(buffers[1]);
}

void Buffer::BindBuffer(SDL_Renderer *rend)
{
	SDL_SetRenderTarget(rend, buffers[activeBuffer]);
	SDL_RenderClear(rend);
}

void Buffer::TAA(SDL_Renderer *rend)
{
	if (firstFrame)
	{
		firstFrame = false;
		return ;
	}
	int previous = (activeBuffer == 1) ? 0 : 1;
	SDL_SetTextureBlendMode(buffers[previous], SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(buffers[previous], 133);
	SDL_Rect rect = {0, 0, gameState.screen.width, gameState.screen.height};
	SDL_RenderCopy(rend, buffers[previous], NULL, &rect);
	SDL_SetTextureAlphaMod(buffers[previous], 255);
}

void Buffer::RenderBuffer(SDL_Renderer *rend)
{

	SDL_SetRenderTarget(rend, NULL);
	SDL_RenderClear(rend);
	SDL_RenderCopy(rend, buffers[activeBuffer], NULL, NULL);
	SDL_RenderPresent(rend);
}

void Buffer::SwapBuffer()
{
	if (activeBuffer == 0)
		activeBuffer = 1;
	else
		activeBuffer = 0;
}
