#include "../inc/Window.hpp"

Window*		Window::_instance = nullptr;
std::mutex	Window::_mtx;

Window::~Window(void)
{
	SDL_DestroyWindow(_sdl_window);
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

SDL_Window*	Window::getWindow(void) const
{
	return (_sdl_window);
}

Window::Window(void)
{
	_sdl_window = SDL_CreateWindow
		("Raytracer", 1920, 1080, 0);
	if (_sdl_window == nullptr)
		throw (std::runtime_error("Failed to create SDL Window"));
}
