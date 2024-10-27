/*
 * First attempt at a c++ game engine using SDL3.
 * Following this resource:
 * https://lazyfoo.net/tutorials/SDL/
 */

//Using SDL and standard IO
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces : uint8_t
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    
    KEY_PRESS_SURFACE_TOTAL // this must be last
};

// The app window
SDL_Window* g_Window = NULL;

// Surface contained by the window
SDL_Surface* g_Surface = NULL;

// Images correspondent to each keypress
SDL_Surface* g_KeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

// Image to render on screen
SDL_Surface* g_CurrentSurface = NULL;

bool init()
{
    // Initializing SDL
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL initialization error: %s\n", SDL_GetError());
        return false;
    }

    // Creating a window
    g_Window = SDL_CreateWindow("Engine", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (g_Window == NULL)
    {
        SDL_Log("SDL Window creation error: %s\n", SDL_GetError());
        return false;
    }

    g_Surface = SDL_GetWindowSurface(g_Window); // gets the surface of the window

    return true;
}

SDL_Surface* loadSurface(const char* path)
{
    // Load image at provided path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path);

    if (loadedSurface == NULL)
    {
        SDL_Log("Failed to load image at '%s': %s\n", path, SDL_GetError());
    }

    return loadedSurface;
}

bool loadMedia()
{
    bool success = true;

    for (uint8_t i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++)
    {
        std::string path = "resources/images/surface_key_" + std::to_string(i) + ".bmp";
        
        g_KeyPressSurfaces[i] = loadSurface(path.c_str());
        if (g_KeyPressSurfaces[i] == NULL)
        {
            printf("Failed to load KeyPressSurfaces index %u\n", i);
            success = false;
        }
    }
    
    return success;
}

void close()
{
    // Deallocate surface
    SDL_DestroySurface(g_CurrentSurface);
    g_CurrentSurface = NULL;

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
    }
    
    bool quit = false;
    SDL_Event e;

    g_CurrentSurface = g_KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
    
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            // User quits the application
            if (e.type == SDL_EVENT_QUIT) quit = true;

            // User presses a key
            else if (e.type == SDL_EVENT_KEY_DOWN)
            {
                // Select surfaces based on key press
                switch (e.key.key)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                    
                case SDLK_UP:
                    g_CurrentSurface = g_KeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                    break;
                case SDLK_DOWN:
                    g_CurrentSurface = g_KeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                    break;
                case SDLK_LEFT:
                    g_CurrentSurface = g_KeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                    break;
                case SDLK_RIGHT:
                    g_CurrentSurface = g_KeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                    break;
                default:
                    g_CurrentSurface = g_KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                    break;
                }
            }
        }

        // Show the image
        SDL_BlitSurface(g_CurrentSurface, NULL, g_Surface, NULL);

        // Update the surface after all frame changes
        SDL_UpdateWindowSurface(g_Window);
    }
    
    close();
    return 0;
}