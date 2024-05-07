
#include "../SDL2/SDL.h"
#include "../../hdr/tools/keys.h"

void eventPoller(t_Keys &keys, int &x, int &y)
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
					keys.click = 1;
				else if (evnt.button.button == SDL_BUTTON_RIGHT)
					keys.rightClick = 1;
				else if (evnt.button.button == SDL_BUTTON_MIDDLE)
				{
					SDL_GetMouseState(&x, &y);
					keys.middleMouse = 1;
				}
				break ;
			case SDL_MOUSEBUTTONUP:
				if (evnt.button.button == SDL_BUTTON_LEFT)
					keys.click = 0;
				else if (evnt.button.button == SDL_BUTTON_RIGHT)
					keys.rightClick = 0;
				else if (evnt.button.button == SDL_BUTTON_MIDDLE)
					keys.middleMouse = 0;
				break ;
			case SDL_MOUSEWHEEL:
				keys.wheel = evnt.wheel.y;
				break ;
			case SDL_KEYDOWN:
				switch (evnt.key.keysym.scancode)
				{
					case SDL_SCANCODE_A:
						keys.a = 1;
						break ;
					case SDL_SCANCODE_D:
						keys.d = 1;
						break ;
					case SDL_SCANCODE_W:
						keys.w = 1;
						break ;
					case SDL_SCANCODE_S:
						keys.s = 1;
						break ;
					case SDL_SCANCODE_SPACE:
						keys.space = 1;
						break ;
					case SDL_SCANCODE_LSHIFT:
						keys.shift = 1;
						break ;
					case SDL_SCANCODE_LEFT:
						keys.left = 1;
						break ;
					case SDL_SCANCODE_RIGHT:
						keys.right = 1;
						break ;
					case SDL_SCANCODE_UP:
						keys.up = 1;
						break ;
					case SDL_SCANCODE_DOWN:
						keys.down = 1;
						break ;
					case SDL_SCANCODE_LCTRL:
						keys.control = 1;
						break ;
					case SDL_SCANCODE_TAB:
						keys.tab = 1;
						break ;
					default:
						break ;
				}
				break ;
			case SDL_KEYUP:
				switch (evnt.key.keysym.scancode)
				{
					case SDL_SCANCODE_A:
						keys.a = 0;
						break ;
					case SDL_SCANCODE_D:
						keys.d = 0;
						break ;
					case SDL_SCANCODE_W:
						keys.w = 0;
						break ;
					case SDL_SCANCODE_S:
						keys.s = 0;
						break ;
					case SDL_SCANCODE_SPACE:
						keys.space = 0;
						break ;
					case SDL_SCANCODE_LSHIFT:
						keys.shift = 0;
						break ;
					case SDL_SCANCODE_LEFT:
						keys.left = 0;
						break ;
					case SDL_SCANCODE_RIGHT:
						keys.right = 0;
						break ;
					case SDL_SCANCODE_UP:
						keys.up = 0;
						break ;
					case SDL_SCANCODE_DOWN:
						keys.down = 0;
						break ;
					case SDL_SCANCODE_LCTRL:
						keys.control = 0;
						break ;
					case SDL_SCANCODE_TAB:
						keys.tab = 0;
						break ;
					default:
						break ;
				}
				break ;
			break ;
		}
	}
}
