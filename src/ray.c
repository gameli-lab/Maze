#include "ben.h"

int map[24][24] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


/**
 * performDDA - Perform DDA to find the point of intersection
 * @ray: ray structure
 * @set: set structure
 * @rayDirX: ray direction on the x-axis
 * @rayDirY: ray direction on the y-axis
 */

void performDDA(Ray *ray, pdp *set, double rayDirX, double rayDirY)
{
	int hit = 0;

	while (hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}

	if (map[ray->mapX][ray->mapY] > 0)
		hit = 1;
	}

    /* Calculate distance projected on camera direction*/
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - set->posX + (1 - ray->stepX) / 2) / rayDirX;
	else
		ray->perpWallDist = (ray->mapY - set->posY + (1 - ray->stepY) / 2) / rayDirY;
}

/**
 * drawScene -  Draws the scene
 * @renderer: calls renderer from SDL
 * @set: structure for player
 */

void drawScene(SDL_Renderer *renderer, pdp *set)
{
	double x, cameraX, rayDirX, rayDirY;

	for (x = 0; x < SCREEN_WIDTH; x++)
	{
		cameraX = 2 * x / (double)SCREEN_WIDTH - 1;/* ray pos n dir */
		rayDirX = set->dirX + set->planeX * cameraX;
		rayDirY = set->dirY + set->planeY * cameraX;

		Ray ray;

		ray.mapX = (int)set->posX;
		ray.mapY = (int)set->posY;
		/* Calc len of ray from one x or y-side to next x or y-side */
		ray.deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		ray.deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		if (rayDirX < 0)/* calculate step and initial sidedist */

		{
			ray.stepX = -1;
			ray.sideDistX = (set->posX - ray.mapX) * ray.deltaDistX;
		}
		else
		{
			ray.stepX = 1;
			ray.sideDistX = (ray.mapX + 1.0 - set->posX) * ray.deltaDistX;
		}
		if (rayDirY < 0)
		{
			ray.stepY = -1;
			ray.sideDistY = (set->posY - ray.mapY) * ray.deltaDistY;
		}
		else
		{
			ray.stepY = 1;
			ray.sideDistY = (ray.mapY + 1.0 - set->posY) * ray.deltaDistY;
		}
		performDDA(&ray, set, rayDirX, rayDirY);
		drawing(renderer, &ray, x);
	}
}


/**
 * drawing - draws to the screen
 * @renderer: renderer from SDL
 * @ray: ray structure
 * @x: reping screen width
 */


void drawing(SDL_Renderer *renderer, Ray *ray, double x)
{
	int lineHeight, drawStart, drawEnd, color;
	/* Calculate height of line to draw on screen */
	lineHeight = (int)(SCREEN_HEIGHT / ray->perpWallDist);

	/* Calculate lowest and highest pixel to fill in current stripe */
	drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (drawEnd >= SCREEN_HEIGHT)
		drawEnd = SCREEN_HEIGHT - 1;

	/* Set wall color */
	color = 128;

	/* Draw the ceiling */
	SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); /* Sky color  ceiling */
	SDL_RenderDrawLine(renderer, x, 0, x, drawStart);

	/* Draw the wall */
	SDL_SetRenderDrawColor(renderer, color, color, color, 255);
	SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);

	/* Draw the ground */
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLine(renderer, x, drawEnd, x, SCREEN_HEIGHT);
}

/**
 * player - Thats our player
 * @renderer: renderer from SDL
 * @set: plane structure
 */

void player(SDL_Renderer *renderer, pdp *set)
{
	/* Draw the player*/
	SDL_Rect playerRect;

	playerRect.x = (int)(set->posX * 10);
	playerRect.y = (int)(set->posY * 10);
	playerRect.w = 5;
	playerRect.h = 5;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); /*color for player*/
	SDL_RenderFillRect(renderer, &playerRect);
}

/**
 * render - renders the graphics
 * @renderer: calls render from SDL
 * @set: structure for player
 */

void render(SDL_Renderer *renderer, pdp *set)
{
	player(renderer, set);
	/* Clear screen */
	SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
	SDL_RenderClear(renderer);

	/* Perform raycasting and draw to screen */
	drawScene(renderer, set);

	/* Update screen */
	SDL_RenderPresent(renderer);
}

