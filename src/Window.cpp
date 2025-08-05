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
	SDL_DisplayID id = SDL_GetPrimaryDisplay();
	if (id == 0)
		throw (std::runtime_error("Failed to get display"));

	SDL_Rect bounds;
	if (!SDL_GetDisplayBounds(id, &bounds))
		throw (std::runtime_error("Failed to get display bounds"));

	_sdl_window = SDL_CreateWindow
		("Raytracer", bounds.w, bounds.h, SDL_WINDOW_FULLSCREEN);
	if (_sdl_window == nullptr)
		throw (std::runtime_error("Failed to create SDL Window"));
}
