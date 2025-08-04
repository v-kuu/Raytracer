#include <SDL3/SDL.h>
#include <iostream>
#include "../inc/raytracer.h"

/*int main(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "Unable to initialize SDL: " << SDL_GetError();
        return 1;
    }
    SDL_Window		*window = nullptr;
	SDL_Renderer	*renderer = nullptr;
	if (!SDL_CreateWindowAndRenderer("Raytracer", 800, 600, 0, &window, &renderer))
	{
		std::cerr << "Could not create window: " << SDL_GetError();
        SDL_Quit();
        return 1;
    }

	// Texture setup
	SDL_Texture	*texture = SDL_CreateTexture
		(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 800, 600);
	if (!texture)
	{
		std::cerr << "Failed to create SDL texture: " << SDL_GetError();
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}
	// Pixel buffer setup
	void	*pixels;
	int		pitch;
	if (!SDL_LockTexture(texture, NULL, &pixels, &pitch))
	{
		std::cerr << "Failed to lock SDL texture: " << SDL_GetError();
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}
	Uint32	*pixel_buffer = (Uint32*)pixels;
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}*/

int	main(void)
{
	Texture *canvas = nullptr;
	try
	{
		canvas = initialize_sdl();
		run_event_loop(canvas);
	}
	catch (std::exception &e)
	{
		std::cerr << "Raytracer error: " << e.what() << std::endl;
		std::cerr << SDL_GetError() << std::endl;
	}
	delete canvas;
	Window::getInstance()->~Window();
	SDL_Quit();
	return (0);
}
