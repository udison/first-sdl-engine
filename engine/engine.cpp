/*
 * First attempt at a c++ game engine using SDL2.
 * Following this resource:
 * https://lazyfoo.net/tutorials/SDL/
 */

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// The app window
SDL_Window* g_Window = NULL;

// Surface contained by the window
SDL_Surface* g_Surface = NULL;

// Image to render on screen
SDL_Surface* g_HelloWorld = NULL;

bool init()
{
    // Initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL initialization error: %s\n", SDL_GetError());
        return false;
    }

    // Creating a window
    g_Window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_Window == NULL)
    {
        printf("SDL Window creation error: %s\n", SDL_GetError());
        return false;
    }

    g_Surface = SDL_GetWindowSurface(g_Window); // gets the surface of the window

    return true;
}

bool loadMedia()
{
    bool success = true;

    // Load the image
    const char* path = "resources/images/test01.bmp";
    g_HelloWorld = SDL_LoadBMP(path);
    if (g_HelloWorld == NULL)
    {
        printf("Failed to load image at '%s': %s\n", path, SDL_GetError());
        success = false;
    }

    // Show the image
    SDL_BlitSurface(g_HelloWorld, NULL, g_Surface, NULL);
    
    return success;
}

void close()
{
    // Deallocate surface
    SDL_FreeSurface(g_HelloWorld);
    g_HelloWorld = NULL;

    // Deallocate window
    SDL_DestroyWindow(g_Window);
    g_Window = NULL;

    // Closes SDLs subsystems
    SDL_Quit();
}

int main(int argc, char* args[])
{
    if (!init())
    {
        return 1;
    }
    
    if (!loadMedia())
    {
        printf("Failed to load media!\n");
        return 1;
    }

    // Update the surface after all frame changes
    SDL_UpdateWindowSurface(g_Window);
    SDL_Event e; bool quit = false; while (!quit) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
    
    close();
    return 0;
}