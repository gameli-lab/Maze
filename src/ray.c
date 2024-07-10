#include "ben.h"

int map[24][24] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 2, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 2, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
	{1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1},
	{1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}
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

void drawScene(SDL_Renderer *renderer, SDL_Texture *wall, SDL_Texture *ground, SDL_Texture *ceiling, pdp *set, int SCREEN_WIDTH, int SCREEN_HEIGHT)
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
		drawing(renderer, wall, ground, ceiling, &ray, x, SCREEN_HEIGHT);
	}
}


/**
 * drawing - draws to the screen
 * @renderer: renderer from SDL
 * @ray: ray structure
 * @x: reping screen width
 */


void drawing(SDL_Renderer *renderer, SDL_Texture *wall, SDL_Texture *ground, SDL_Texture *ceiling, Ray *ray, double x, int SCREEN_HEIGHT)
{
	int lineHeight, drawStart, drawEnd, y;
	SDL_Rect wallRect, groundRect, ceilingRect/*, rect*/;
	/* Calculate height of line to draw on screen */
	lineHeight = (int)(SCREEN_HEIGHT / ray->perpWallDist);

	/* Calculate lowest and highest pixel to fill in current stripe */
	drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (drawEnd >= SCREEN_HEIGHT)
		drawEnd = SCREEN_HEIGHT - 1;

	/* Draw the ceiling */
	for (y = 0; y < drawStart; y += TILE_SIZE)
	{
		ceilingRect = (SDL_Rect){x, y, 1, TILE_SIZE};
		SDL_RenderCopy(renderer, ceiling, NULL, &ceilingRect);
	}

	/* Draw the wall */
	wallRect = (SDL_Rect){x, drawStart, 1, drawEnd - drawStart};
	SDL_RenderCopy(renderer, wall, NULL, &wallRect);

	/* Draw the ground */
	for (y = drawEnd; y < SCREEN_HEIGHT; y += TILE_SIZE)
	{
		groundRect = (SDL_Rect){x, y, 1, TILE_SIZE};
		SDL_RenderCopy(renderer, ground, NULL, &groundRect);
	}
}
