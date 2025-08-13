#include "../inc/Texture.hpp"

Texture::Texture(std::shared_ptr<Renderer> renderer) : _renderer(renderer)
{
	int width, height;

	if (!SDL_GetWindowSizeInPixels
			(Window::getInstance()->getWindow(), &width, &height))
			throw (std::runtime_error("Failed to get window size"));

	_texture = SDL_CreateTexture(
				renderer->getRenderer(),
				SDL_PIXELFORMAT_RGBA8888,
				SDL_TEXTUREACCESS_STREAMING,
				width, height);

	if (_texture == nullptr)
		throw (std::runtime_error("Failed to create SDL texture"));
}

Texture::~Texture(void)
{
	SDL_DestroyTexture(_texture);
}

SDL_Texture*	Texture::getTexture(void)
{
	return (_texture);
}

std::shared_ptr<Renderer>	Texture::getRenderer(void)
{
	return (_renderer);
}
