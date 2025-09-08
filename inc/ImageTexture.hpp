#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "ITexture.hpp"
#include <string>
#include <filesystem>
#include <algorithm>
#include <vector>

class	ImageTexture : public ITexture
{
	public:
		ImageTexture(void) = delete;
		ImageTexture(const std::string &filename);

		Vec3 lookup(float u, float v, const Vec3 &point) override;

	private:
		std::vector<Vec3> _texels;
		int _width, _height;
	
		Vec3	_getRGB(Uint32 color, const SDL_PixelFormatDetails *format);
};
