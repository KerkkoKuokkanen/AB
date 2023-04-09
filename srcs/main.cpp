
#include "../hdr/ab.h"

void init(t_wr *wr)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(26);
	SDL_CreateWindowAndRenderer(1920, 1080, 0, &wr->win, &wr->rend);
	SDL_SetRenderDrawBlendMode(wr->rend, SDL_BLENDMODE_BLEND);
	//SDL_SetWindowFullscreen(wre->win, window_check_value);
	//SDL_ShowCursor(SDL_DISABLE);
}

int main()
{
	SDL_Event evnt;
	t_wr wr;
	init(&wr);

	while (1)
	{
		while (SDL_PollEvent(&evnt))
		{
			if (evnt.type == SDL_QUIT)
				exit(0);
		}
		SDL_RenderClear(wr.rend);
		SDL_RenderPresent(wr.rend);
	}

	return (0);
}