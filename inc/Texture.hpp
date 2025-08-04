#pragma once
#include <SDL3/SDL.h>
#include "Renderer.hpp"

class	Texture
{
	public:
		Texture(Renderer *renderer);
		~Texture(void);

		SDL_Texture	*getTexture(void);
		Renderer	*getRenderer(void);

	private:
		SDL_Texture	*_texture;
		Renderer	*_renderer;
};
