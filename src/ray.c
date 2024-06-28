#include "ben.h"

int map[24][24] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


/* Perform DDA to find the point of intersection */
void performDDA(Ray *ray, pdp *set, double rayDirX, double rayDirY) {
    int hit = 0;

    while (hit == 0) {
        if (ray->sideDistX < ray->sideDistY) {
            ray->sideDistX += ray->deltaDistX;
            ray->mapX += ray->stepX;
            ray->side = 0;
        } else {
            ray->sideDistY += ray->deltaDistY;
            ray->mapY += ray->stepY;
            ray->side = 1;
        }
        // Check if ray has hit a wall
        if (map[ray->mapX][ray->mapY] > 0) hit = 1;
    }

    // Calculate distance projected on camera direction
    if (ray->side == 0)
        ray->perpWallDist = (ray->mapX - set->posX + (1 - ray->stepX) / 2) / rayDirX;
    else
        ray->perpWallDist = (ray->mapY - set->posY + (1 - ray->stepY) / 2) / rayDirY;
}

// Draw the scene
void drawScene(SDL_Renderer* renderer, pdp *set) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        // Calculate ray position and direction
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1; // X-coordinate in camera space
        double rayDirX = set->dirX + set->planeX * cameraX;
        double rayDirY = set->dirY + set->planeY * cameraX;

        // Initialize ray structure
        Ray ray;
        ray.mapX = (int)set->posX;
        ray.mapY = (int)set->posY;

        // Calculate length of ray from one x or y-side to next x or y-side
        ray.deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        ray.deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        // Calculate step and initial sideDist
        if (rayDirX < 0) {
            ray.stepX = -1;
            ray.sideDistX = (set->posX - ray.mapX) * ray.deltaDistX;
        } else {
            ray.stepX = 1;
            ray.sideDistX = (ray.mapX + 1.0 - set->posX) * ray.deltaDistX;
        }
        if (rayDirY < 0) {
            ray.stepY = -1;
            ray.sideDistY = (set->posY - ray.mapY) * ray.deltaDistY;
        } else {
            ray.stepY = 1;
            ray.sideDistY = (ray.mapY + 1.0 - set->posY) * ray.deltaDistY;
        }

        // Perform DDA
        performDDA(&ray, set, rayDirX, rayDirY);

        // Calculate height of line to draw on screen
        int lineHeight = (int)(SCREEN_HEIGHT / ray.perpWallDist);

        // Calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

        // Set wall color
        int color = 128; // Gray color for walls

	        // Choose wall color
        /*SDL_Color color;
        switch(map[ray.mapX][ray.mapY]) {
            case 1: color = (SDL_Color){255, 0, 0, 255}; break; // Red
            case 2: color = (SDL_Color){0, 255, 0, 255}; break; // Green
            case 3: color = (SDL_Color){0, 0, 255, 255}; break; // Blue
            case 4: color = (SDL_Color){255, 255, 255, 255}; break; // White
            default: color = (SDL_Color){255, 255, 0, 255}; break; // Yellow
        }

        // Give x and y sides different brightness
        if (ray.side == 1) {
            color.r /= 2;
            color.g /= 2;
            color.b /= 2;
        }

        // Draw the vertical line
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
    */


        // Draw the ceiling
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Sky blue color for ceiling
        SDL_RenderDrawLine(renderer, x, 0, x, drawStart);

        // Draw the wall
        SDL_SetRenderDrawColor(renderer, color, color, color, 255);
        SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);

        // Draw the ground
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color for ground
        SDL_RenderDrawLine(renderer, x, drawEnd, x, SCREEN_HEIGHT);
    }

    // Draw the player
    SDL_Rect playerRect;
    playerRect.x = (int)(set->posX * 10);
    playerRect.y = (int)(set->posY * 10);
    playerRect.w = 5;
    playerRect.h = 5;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for player
    SDL_RenderFillRect(renderer, &playerRect);
}

 void rotateCam(pdp *set, double angle) {
	double old_dirX = set->dirX;
	double old_planeX = set->planeX;

	set->dirX = set->dirX * cos(angle) - set->dirY *sin(angle);
	set->dirY = old_dirX * sin(angle) + set->dirY * cos(angle);
	set->planeX = set->planeX * cos(angle) - set->planeY * sin(angle);
	set->planeY = old_planeX * sin(angle) + set->planeY * cos(angle);
 }


int init_SDL(SDL_Window **window, SDL_Renderer **renderer) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // Create window
    *window = SDL_CreateWindow("Gameli's Maze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    // Create renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 0;
    }
    return (1);
}


void input(pdp *set) {
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                exit(0);
            }
	    else if (e.type == SDL_KEYDOWN) {
		    switch (e.key.keysym.sym) {
			    case SDLK_UP:
				    if (map[(int)(set->posX + set->dirX * 0.5)][(int)set->posY] == 0) set->posX += set->dirX * 0.5;
				    if (map[(int)set->posX][(int)(set->posY + set->dirY * 0.5)] == 0) set->posY += set->dirY * 0.5;
				    break;
			    case SDLK_DOWN:
				    if (map[(int)(set->posX - set->dirX * 0.5)][(int)set->posY] == 0) set->posX -= set->dirX * 0.5;
				    if (map[(int)set->posX][(int)(set->posY - set->dirY * 0.5)] == 0) set->posY -= set->dirY * 0.5;
				    break;
			    case SDLK_LEFT:
				    rotateCam(set, 0.1);
				    break;
			    case SDLK_RIGHT:
				    rotateCam(set, -0.1);
				    break;
		    }
	    }
    }
}

void render(SDL_Renderer *renderer, pdp *set) {
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Sky blue color for ceiling
        SDL_RenderClear(renderer);

        // Perform raycasting and draw to screen
        drawScene(renderer, set);

        // Update screen
        SDL_RenderPresent(renderer);
}

    // Destroy window
void close_SDL(SDL_Renderer *renderer, SDL_Window *window) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
