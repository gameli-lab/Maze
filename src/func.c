#include "ben.h"

/**
 * rotateCam - rotates camera
 * @set: structure for player
 * @angle: angle of the player
 */

void rotateCam(pdp *set, double angle)
{
	double old_dirX = set->dirX;
	double old_planeX = set->planeX;

	set->dirX = set->dirX * cos(angle) - set->dirY * sin(angle);
	set->dirY = old_dirX * sin(angle) + set->dirY * cos(angle);
	set->planeX = set->planeX * cos(angle) - set->planeY * sin(angle);
	set->planeY = old_planeX * sin(angle) + set->planeY * cos(angle);
}

/**
 * init_SDL - initiates SDL
 * @window: window to create
 * @renderer: renders graphics
 *
 * Return: returns 1 on success else 0
 */

int init_SDL(SDL_Window **window, SDL_Renderer **renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
	printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	return (0);
	}

	*window = SDL_CreateWindow("Gameli's Maze", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_RESIZABLE);
	if (*window == NULL)
	{
	printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	SDL_Quit();
	return (0);
	}

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (*renderer == NULL)
	{
	printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
	SDL_DestroyWindow(*window);
	SDL_Quit();
	return (0);
	}
	return (1);
}

/**
 * input - handles keyboard input
 * @set: structurefor player
 */

void input(pdp *set, int *SCREEN_WIDTH, int *SCREEN_HEIGHT)
{
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			exit(0);
		}
		else if (e.type == SDL_KEYDOWN)
		{
			if ((e.key.keysym.sym == SDLK_UP) || (e.key.keysym.sym == SDLK_w))
			{
				if (map[(int)(set->posX + set->dirX * 0.5)][(int)set->posY] == 0)
					set->posX += set->dirX * 0.5;
				if (map[(int)set->posX][(int)(set->posY + set->dirY * 0.5)] == 0)
					set->posY += set->dirY * 0.5;
			}
			else if ((e.key.keysym.sym == SDLK_DOWN) || (e.key.keysym.sym == SDLK_s))
			{
				if (map[(int)(set->posX - set->dirX * 0.5)][(int)set->posY] == 0)
					set->posX -= set->dirX * 0.5;
				if (map[(int)set->posX][(int)(set->posY - set->dirY * 0.5)] == 0)
					set->posY -= set->dirY * 0.5;
			}
			else if ((e.key.keysym.sym == SDLK_LEFT) || (e.key.keysym.sym == SDLK_a))
				rotateCam(set, -0.1);

			else if ((e.key.keysym.sym == SDLK_RIGHT) || (e.key.keysym.sym == SDLK_d))
				rotateCam(set, 0.1);
		}
		else if (e.type == SDL_WINDOWEVENT)
			if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				*SCREEN_WIDTH = e.window.data1;
				*SCREEN_HEIGHT = e.window.data2;
			}
	}
}

/**
 * close_SDL - destroys SDL stuff
 * @renderer: renderer to destroy
 * @window: window to destroy
 */
void close_SDL(SDL_Renderer *renderer, SDL_Window *window)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


SDL_Texture *load_texture(SDL_Renderer *renderer, const char *file)
{
	SDL_Surface *surface = IMG_Load(file);
	if(!surface)
	{
		printf("Error loading image : %s\n", IMG_GetError());
		return NULL;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!surface)
		printf("Error creating texture: %s\n", SDL_GetError());
	return (texture);
}
