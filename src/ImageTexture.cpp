#include "../inc/ImageTexture.hpp"

ImageTexture::ImageTexture(const std::string &filename)
{
	std::filesystem::path source_dir = std::filesystem::path(__FILE__).parent_path();
	std::filesystem::path filepath = source_dir / ".." / "textures" / filename;
	filepath = std::filesystem::weakly_canonical(filepath);
	SDL_Surface *buffer = IMG_Load(filepath.c_str());
	if (buffer == nullptr)
		throw (std::runtime_error("ImageTexture file error"));
	const SDL_PixelFormatDetails *format = SDL_GetPixelFormatDetails(buffer->format);
	if (!buffer)
	{
		SDL_DestroySurface(buffer);
		throw (std::runtime_error("Failed to fetch pixel format details"));
	}
	Uint32 *pixel_buffer = static_cast<Uint32*>(buffer->pixels);
	_width = buffer->w;
	_height = buffer->h;
	for (int y = 0; y < _height; ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
		Uint32 color = pixel_buffer[y * (buffer->pitch / sizeof(Uint32)) + x];
		_texels.push_back(_getRGB(color, format));
		}
	}
	SDL_DestroySurface(buffer);
}

Vec3	ImageTexture::lookup(float u, float v, const Vec3 &point)
{
	(void)point;
	u = std::clamp(u, 0.0f, 1.0f);
	v = std::clamp(v, 0.0f, 1.0f);
	int x = static_cast<int>(u * (_width - 1));
	int y = static_cast<int>(v * (_height - 1));
	return (_texels[y * _width + x]);
}

Vec3	ImageTexture::_getRGB(Uint32 color, const SDL_PixelFormatDetails *format)
{
	Uint8 r, g, b;
	SDL_GetRGB(color, format, NULL, &r, &g, &b);
	float red = r / 255.0f;
	float green = g / 255.0f;
	float blue = b / 255.0f;
	return (Vec3(red, green, blue));
}
