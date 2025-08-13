#pragma once
#include <memory>
#include <SDL3/SDL.h>
#include "Renderer.hpp"

class	Texture
{
	public:
		Texture(std::shared_ptr<Renderer> renderer);
		~Texture(void);

		SDL_Texture					*getTexture(void);
		std::shared_ptr<Renderer>	getRenderer(void);

	private:
		SDL_Texture					*_texture;
		std::shared_ptr<Renderer>	_renderer;
};
