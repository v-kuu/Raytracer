#include "../inc/Texture.hpp"

Texture::Texture(Renderer *renderer) : _renderer(renderer)
{
	int w, h;
	if (!SDL_GetRenderOutputSize(renderer->getRenderer(), &w, &h))
		throw (std::runtime_error("Failed to get renderer dimensions"));

	_texture = SDL_CreateTexture(
				renderer->getRenderer(),
				SDL_PIXELFORMAT_RGBA8888,
				SDL_TEXTUREACCESS_STREAMING,
				w, h);

	if (_texture == nullptr)
		throw (std::runtime_error("Failed to create SDL texture"));
}

Texture::~Texture(void)
{
	SDL_DestroyTexture(_texture);
	delete _renderer;
}

SDL_Texture*	Texture::getTexture(void)
{
	return (_texture);
}

Renderer*	Texture::getRenderer(void)
{
	return (_renderer);
}
