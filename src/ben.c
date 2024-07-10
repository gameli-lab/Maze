#include "ben.h"

/**
 * init_SDLimage - initiates SDL image
 *
 * Return: 0 on success else 1
 */

int init_SDLimage(void)
{
	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("Error initiating SDL_Image: %s\n", IMG_GetError());
		IMG_Quit();
		return (1);
	}
	return (0);
}



/**
 * main - this is the main program
 *
 * Return: 0 on seccess else 1
 */

int main(void)
{
	pdp set = {1, 2, 1, 0, 0, 0.66};
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *wall = NULL, *ground = NULL, *ceiling = NULL;
	int SCREEN_WIDTH = 1355, SCREEN_HEIGHT = 768;

	if (!init_SDL(&window, &renderer, SCREEN_WIDTH, SCREEN_HEIGHT))
		return (1);

	if (init_SDLimage())
	{
		close_SDL(renderer, window);
		return (1);
	}

	/*wall = load_texture(renderer, "./img/brickwall.jpg");
	ground = load_texture(renderer, "./img/grass.png");*/
	ceiling = load_texture(renderer, "./img/sky.jpg");
	/*wall = load_texture(renderer, "./img/brickwall.jpg");*/
	ground = load_texture(renderer, "./img/grass.png");
	wall = load_texture(renderer, "./img/brickwall.jpg");

	if (!wall || !ground || !ceiling)
	{
		close_SDL(renderer, window);
		DestroyTexture(wall, ground, ceiling);
		return 1;
	}


	int running = 1;

	while (running)
	{
		SDL_RenderClear(renderer);
		input(&set, &SCREEN_WIDTH, &SCREEN_HEIGHT);
		drawScene(renderer, wall, ground, ceiling, &set, SCREEN_WIDTH, SCREEN_HEIGHT);
		small_map(renderer, &set, SCREEN_HEIGHT);
		SDL_RenderPresent(renderer);
	}
	close_SDL(renderer, window);
	DestroyTexture(wall, ground, ceiling);
	IMG_Quit();
	return (0);
}

void DestroyTexture(SDL_Texture *wall, SDL_Texture *ground, SDL_Texture *ceiling)
{
	SDL_DestroyTexture(wall);
	SDL_DestroyTexture(ground);
	SDL_DestroyTexture(ceiling);
}
