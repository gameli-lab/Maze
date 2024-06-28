#ifndef BEN_H
#define BEN_H

#include <stdio.h>
#include <SDL2/SDL.h>
/*#include <maths.h>*/

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 720

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
void drawScene(SDL_Renderer *renderer, pdp *set);
void rotateCam(pdp *set, double angle);
int init_SDL(SDL_Window **window, SDL_Renderer **renderer);
void input(pdp *set);
void render(SDL_Renderer *renderer, pdp *set);
void close_SDL(SDL_Renderer *renderer, SDL_Window *window);

#endif /* BEN_H */
