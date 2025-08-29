#pragma once
#include <SDL3/SDL.h>
#include "Window.hpp"

class	Renderer
{
	public:
		Renderer(Window *window);
		~Renderer(void);

		SDL_Renderer*	getRenderer(void) const;

	private:
		SDL_Renderer	*_renderer;

		Renderer(void);
};
