#ifndef BEN_H
#define BEN_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define TILE_SIZE 24

typedef struct {
	int mapX, mapY;
	int stepX, stepY;
	int side;
	double sideDistX, sideDistY;
	double deltaDistX, deltaDistY;
	double perpWallDist;
} Ray;

typedef struct {
	double posX, posY;
	double dirX, dirY;
	double planeX, planeY;
} pdp;

extern int map[24][24];

void performDDA(Ray *ray, pdp *set, double rayDirX, double rayDirY);
void drawScene(SDL_Renderer *renderer, SDL_Texture *wall, SDL_Texture *ground, SDL_Texture *ceiling, pdp *set, int SCREEN_WIDTH, int SCREEN_HEIGHT);
void rotateCam(pdp *set, double angle);
int init_SDL(SDL_Window **window, SDL_Renderer **renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
int init_SDLimage(void);
void input(pdp *set, int *SCREEN_WIDTH, int *SCREEN_HEIGHT);
void close_SDL(SDL_Renderer *renderer, SDL_Window *window);
void drawing(SDL_Renderer *renderer, SDL_Texture *wall, SDL_Texture *ground, SDL_Texture *ceiling, Ray *ray, double x, int SCREEN_HEIGHT);
SDL_Texture *load_texture(SDL_Renderer * renderer, const char *file);
void DestroyTexture( SDL_Texture *wall, SDL_Texture *ground, SDL_Texture *ceiling);
void small_map(SDL_Renderer *renderer, pdp *set, int SCREEN_HEIGHT);

#endif /* BEN_H */
