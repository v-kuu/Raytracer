#pragma once
#include <SDL3/SDL.h>
#include "Renderer.hpp"

class	Texture
{
	public:
		Texture(Renderer &renderer);
		~Texture(void);

		SDL_Texture	*getTexture(void);

	private:
		SDL_Texture	*_texture;
};
