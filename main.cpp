#include <SDL3/SDL.h>

int main(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
	{
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "SDL3 Window",
        800, 600,                // width, height
        0                        // flags
    );

    if (!window)
	{
        SDL_Log("Could not create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Delay(2000);  // Show the window for 2 seconds

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
