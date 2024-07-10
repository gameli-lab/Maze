#include "ben.h"

/**
 * small_map - map of the game
 * @renderer: renders the map
 * @set: players params
 */

void small_map(SDL_Renderer *renderer, pdp *set, int SCREEN_HEIGHT)
{
	int map_scale = 5, x, y;
	int map_size = 24 * map_scale;
	SDL_Rect tile, player;

	for (y = 0; y < 24; y++)
	{
		for (x = 0; x < 24; x++)
		{
			tile.x = x * map_scale;
			tile.y = SCREEN_HEIGHT - map_size + y * map_scale;
			tile.w = map_scale;
			tile.h = map_scale;

			if (map[y][x] == 1)
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			else
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(renderer, &tile);
		}
	}

	player.x = (int)(set->posX * map_scale);
	player.y = SCREEN_HEIGHT - map_size + (int)(set->posY * map_scale);
	player.w = map_scale;
	player.h = map_scale;

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &player);
}
