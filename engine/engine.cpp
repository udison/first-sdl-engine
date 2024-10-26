/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
    // The app window
    SDL_Window *window = NULL;

    // Surface contained by the window
    SDL_Surface *surface = NULL;

    // Initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        return 1;
    }

    surface = SDL_GetWindowSurface(window); // gets the surface of the window
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF)); // paints the window white
    SDL_UpdateWindowSurface(window); // update its surface in order to show thing that were drawn
    SDL_Event e; bool quit = false; while (!quit) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } } // forces the window to stay open

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}