
#include "../../hdr/ow/owHeader.h"

static int	figure_the_delay(clock_t start, clock_t end)
{
	double	time;
	int		ret;
	time = 0.0;
	time += (double)(end - start) / CLOCKS_PER_SEC;
	ret = FRAME - (int)(time * 1000.0f);
	if (ret < 0)
		return (0);
	else
		return (ret);
}

void OverWorldLoop()
{
	clock_t start, end;
	int fakeX = 0, fakeY = 0;
	while (true)
	{
		start = clock();
		eventPoller(owState.owKeys, fakeX, fakeY);
		owState.renderer->RenderAll();
		end = clock();
		SDL_Delay(figure_the_delay(start, end));
	}
}
