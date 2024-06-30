#include "ben.h"

/*
 * pdp set = {22, 12, -1, 0, 0, 0.66};
 */

/**
 * main - this is the main program
 *
 * Return: 0 on seccess else 1
 */

int main(void)
{
	pdp set = {1, 2, -1, 0, 0, 0.66};
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if (!init_SDL(&window, &renderer))
	{
		return (1);
	}

	int running = 1;

	while (running)
	{
		input(&set);
		render(renderer, &set);
	}
	close_SDL(renderer, window);
	return (0);
}
