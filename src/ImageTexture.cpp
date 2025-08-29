#include "../inc/ImageTexture.hpp"

ImageTexture::ImageTexture(const std::string &filename)
{
	std::filesystem::path filepath = std::filesystem::current_path() / "textures" / filename;
	_buffer = SDL_LoadBMP(filepath.c_str());
	if (_buffer == nullptr)
		throw (std::runtime_error("ImageTexture file error"));
	_pixel_buffer = static_cast<Uint32*>(_buffer->pixels);
}

ImageTexture::~ImageTexture(void)
{
	SDL_DestroySurface(_buffer);
}

Vec3	ImageTexture::lookup(float u, float v, const Vec3 &point)
{
	(void)point;
	int x = static_cast<int>(std::round(u * (_buffer->w - 1)));
	int y = static_cast<int>(std::round(v * (_buffer->w - 1)));
	Uint32 color = _pixel_buffer[y * (_buffer->pitch / sizeof(Uint32)) + x];
	float red = static_cast<float>((color >> 24 & 0xFF) / 255.0f);
	float green = static_cast<float>((color >> 16 & 0xFF) / 255.0f);
	float blue = static_cast<float>((color >> 8 & 0xFF) / 255.0f);
	return (Vec3(red, green, blue));
}
