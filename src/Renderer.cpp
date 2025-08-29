#include "../inc/Renderer.hpp"

Renderer::Renderer(Window *window)
{
	_renderer = SDL_CreateRenderer(window->getWindow(), NULL);
	if (_renderer == nullptr)
		throw (std::runtime_error("Unable to create SDL renderer"));
}

SDL_Renderer*	Renderer::getRenderer(void) const
{
	return (_renderer);
}

Renderer::~Renderer(void)
{
	SDL_DestroyRenderer(_renderer);
}
