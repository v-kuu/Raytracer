#include <SDL3/SDL.h>
#include <iostream>

int main(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "Unable to initialize SDL: " << SDL_GetError();
        return 1;
    }
	// Window and renderer setup
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
	for (int i = 0; i < 800 * 600; ++i)
	{
		Uint32 pixel_color = SDL_MapRGBA(SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888), NULL,
				i % 255, (i / 255) % 255, (i / (255 * 255)) % 255, 255);
		pixel_buffer[i] = pixel_color;
	}
	SDL_UnlockTexture(texture);
	SDL_RenderClear(renderer);
	SDL_RenderTexture(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
    SDL_Delay(2000);
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
