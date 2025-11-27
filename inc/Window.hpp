// try to implement simpleton
#pragma once
#include <SDL3/SDL.h>
#include <mutex>
#include <stdexcept>

class	Window
{
	public:
		~Window(void);
		Window(const Window &other) = delete;
		Window	&operator=(const Window &other) = delete;

		static Window	*getInstance(void);

		SDL_Window		*getWindow(void) const;

	private:
		static Window		*_instance;
		static std::mutex	_mtx;
		SDL_Window			*_sdl_window;

		Window(void);
};
