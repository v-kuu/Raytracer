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
			throw (std::runtime_error("Failed to get texture size"));
		}
		for (int i = 0; i < y; ++i)
		{
			for (int j = 0; j < x; ++j)
			{
				Uint32 pixel_color =
					//(i % 255 << 24 | (i / 255) % 255 << 16 |
					 //(i / (255 * 255)) % 255 << 8 | 255);
					 (255 << 24 | 255 << 16 | 255 << 8 | 255);
				pixel_buffer[i * (pitch / sizeof(Uint32)) + j] = pixel_color;
			}
		}
		SDL_UnlockTexture(canvas->getTexture());
		SDL_RenderClear(rnd->getRenderer());
		SDL_RenderTexture(rnd->getRenderer(), canvas->getTexture(), NULL, NULL);
		SDL_RenderPresent(rnd->getRenderer());
		SDL_Delay(2000);
		break ;
	}
}
