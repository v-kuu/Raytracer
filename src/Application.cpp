#include "../inc/Application.hpp"

Application::Application(void) : _renderer(nullptr), _canvas(nullptr)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw (std::runtime_error("Unable to initialize SDL"));
	try
	{
		Window::getInstance();
	}
	catch (std::exception)
	{
		throw ;
	}
	try
	{
		_renderer = new Renderer(Window::getInstance());
		_canvas = new Texture(_renderer);
	}
	catch (std::exception)
	{
		throw ;
	}
}

Application::~Application(void)
{
	delete _canvas;
	try
	{
		Window::getInstance()->~Window();
	}
	catch (std::exception)
	{
	}
	SDL_Quit();
}

void	Application::run(void)
{
	void	*pixels;
	Uint32	*pixel_buffer;
	int		pitch;

	while (true)
	{
		if (!SDL_LockTexture(_canvas->getTexture(), NULL, &pixels, &pitch))
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
					(i % 255 << 24 | (i / 255) % 255 << 16 |
					(i / (255 * 255)) % 255 << 8 | 255);
				pixel_buffer[i * (pitch / sizeof(Uint32)) + j] = pixel_color;
			}
		}
		SDL_UnlockTexture(_canvas->getTexture());
		SDL_RenderClear(_renderer->getRenderer());
		SDL_RenderTexture(_renderer->getRenderer(), _canvas->getTexture(), NULL, NULL);
		SDL_RenderPresent(_renderer->getRenderer());
		SDL_Delay(2000);
		break ;
	}
}
