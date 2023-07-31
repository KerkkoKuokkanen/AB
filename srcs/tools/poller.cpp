
#include "../../hdr/ab.h"
#include "../../hdr/global.h"

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
				else if (evnt.button.button == SDL_BUTTON_RIGHT)
					gameState.keys.rightClick = 1;
				else if (evnt.button.button == SDL_BUTTON_MIDDLE)
				{
					SDL_GetMouseState(&gameState.camera.clickTimePosX, &gameState.camera.clickTimePosY);
					gameState.keys.middleMouse = 1;
				}
				break ;
			case SDL_MOUSEBUTTONUP:
				if (evnt.button.button == SDL_BUTTON_LEFT)
					gameState.keys.click = 0;
				else if (evnt.button.button == SDL_BUTTON_RIGHT)
					gameState.keys.rightClick = 0;
				else if (evnt.button.button == SDL_BUTTON_MIDDLE)
					gameState.keys.middleMouse = 0;
				break ;
			case SDL_MOUSEWHEEL:
				gameState.keys.wheel = evnt.wheel.y;
				break ;
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
					case SDL_SCANCODE_SPACE:
						gameState.keys.space = 1;
						break ;
					case SDL_SCANCODE_LSHIFT:
						gameState.keys.shift = 1;
						break ;
					case SDL_SCANCODE_LEFT:
						gameState.keys.left = 1;
						break ;
					case SDL_SCANCODE_RIGHT:
						gameState.keys.right = 1;
						break ;
					case SDL_SCANCODE_UP:
						gameState.keys.up = 1;
						break ;
					case SDL_SCANCODE_DOWN:
						gameState.keys.down = 1;
						break ;
					case SDL_SCANCODE_LCTRL:
						gameState.keys.control = 1;
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
					case SDL_SCANCODE_SPACE:
						gameState.keys.space = 0;
						break ;
					case SDL_SCANCODE_LSHIFT:
						gameState.keys.shift = 0;
						break ;
					case SDL_SCANCODE_LEFT:
						gameState.keys.left = 0;
						break ;
					case SDL_SCANCODE_RIGHT:
						gameState.keys.right = 0;
						break ;
					case SDL_SCANCODE_UP:
						gameState.keys.up = 0;
						break ;
					case SDL_SCANCODE_DOWN:
						gameState.keys.down = 0;
						break ;
					case SDL_SCANCODE_LCTRL:
						gameState.keys.control = 0;
						break ;
					default:
						break ;
				}
				break ;
			break ;
		}
	}
}
