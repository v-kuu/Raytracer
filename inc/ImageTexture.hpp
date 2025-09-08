#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "ITexture.hpp"
#include <string>
#include <filesystem>

class	ImageTexture : public ITexture
{
	public:
		ImageTexture(void) = delete;
		~ImageTexture(void);
		ImageTexture(const std::string &filename);

		Vec3	lookup(float u, float v, const Vec3 &point) override;

	private:
		SDL_Surface	*_buffer;
		Uint32		*_pixel_buffer;
};
