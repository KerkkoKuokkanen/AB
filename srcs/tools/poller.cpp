
#include "../../hdr/ab.h"

void eventPoller()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				exit(0);
			case SDL_MOUSEBUTTONDOWN:
				if (evnt.button.button == SDL_BUTTON_LEFT)
					gameState.keys.click = 1;
				break ;
			case SDL_MOUSEBUTTONUP:
				if (evnt.button.button == SDL_BUTTON_LEFT)
					gameState.keys.click = 0;
			case SDL_KEYDOWN:
				switch (evnt.key.keysym.scancode)
				{
					case SDL_SCANCODE_A:
						gameState.keys.a = 1;
						break ;
					case SDL_SCANCODE_D:
						gameState.keys.d = 1;
						break ;
					case SDL_SCANCODE_W:
						gameState.keys.w = 1;
						break ;
					case SDL_SCANCODE_S:
						gameState.keys.s = 1;
						break ;
					default:
						break ;
				}
				break ;
			case SDL_KEYUP:
				switch (evnt.key.keysym.scancode)
				{
					case SDL_SCANCODE_A:
						gameState.keys.a = 0;
						break ;
					case SDL_SCANCODE_D:
						gameState.keys.d = 0;
						break ;
					case SDL_SCANCODE_W:
						gameState.keys.w = 0;
						break ;
					case SDL_SCANCODE_S:
						gameState.keys.s = 0;
						break ;
					default:
						break ;
				}
				break ;
			break ;
		}
	}
}
