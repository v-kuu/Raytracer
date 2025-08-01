#include "../inc/Window.hpp"

Window::~Window(void)
{
	SDL_DestroyWindow(_sdl_window);
	delete (_instance);
}

Window*	Window::getInstance(void)
{
	if (_instance == nullptr)
	{
		std::lock_guard<std::mutex> lock(_mtx);
		if (_instance == nullptr)
			_instance = new Window();
	}
	return (_instance);
}

Window::Window(void)
{
	_sdl_window = SDL_CreateWindow
		("Raytracer", 1920, 1080, SDL_WINDOW_FULLSCREEN);
	if (_sdl_window == nullptr)
		throw (std::runtime_error("Failed to create SDL Window"));
}
