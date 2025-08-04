#include "../inc/raytracer.h"

void	run_event_loop(Texture *canvas)
{
	void	*pixels;
	Uint32	*pixel_buffer;
	int		pitch;

	Renderer	*rnd = canvas->getRenderer();
	while (true)
	{
		if (!SDL_LockTexture(canvas->getTexture(), NULL, &pixels, &pitch))
			throw (std::runtime_error("Could not lock SDL texture"));
		pixel_buffer = static_cast<Uint32*>(pixels);
		//render frame
		int	x, y;
		if (!SDL_GetWindowSizeInPixels(Window::getInstance()->getWindow(), &x, &y))
		{
			throw (std::runtime_error("Failed to get window size"));
		}
		for (int i = 0; i < x * y; ++i)
		{
			Uint32 pixel_color = SDL_MapRGBA(SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888), NULL,
					i % 255, (i / 255) % 255, (i / (255 * 255)) % 255, 255);
			pixel_buffer[i] = pixel_color;
		}
		SDL_UnlockTexture(canvas->getTexture());
		SDL_RenderClear(rnd->getRenderer());
		SDL_RenderTexture(rnd->getRenderer(), canvas->getTexture(), NULL, NULL);
		SDL_RenderPresent(rnd->getRenderer());
		SDL_Delay(2000);
		break ;
	}
}
