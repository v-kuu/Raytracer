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
	if (!format)
	{
		SDL_DestroySurface(buffer);
		throw (std::runtime_error("Failed to fetch pixel format details"));
	}
	bool linear = _detectLinear(filename);
	if (linear)
	{
		SDL_Surface *converted = SDL_ConvertSurfaceAndColorspace(buffer, buffer->format, nullptr, SDL_COLORSPACE_SRGB_LINEAR, 0);
		SDL_DestroySurface(buffer);
		if (!converted)
			throw (std::runtime_error("Failed to convert surface to linear colorspace"));
		buffer = converted;
	}
	Uint32 *pixel_buffer = static_cast<Uint32*>(buffer->pixels);
	_width = buffer->w;
	_height = buffer->h;
	for (int y = 0; y < _height; ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
		Uint32 color = pixel_buffer[y * (buffer->pitch / sizeof(Uint32)) + x];
		Vec3 final = _getRGB(color, format);
		//if (!linear)
			final = pow(final, 1/2.2f);
		_texels.push_back(final);
		}
	}
	SDL_DestroySurface(buffer);
}

// Inludes bilinear filtering
Vec3	ImageTexture::lookup(float u, float v, const Vec3 &point)
{
	(void)point;
	u = std::clamp(u, 0.0f, 1.0f);
	v = std::clamp(v, 0.0f, 1.0f);

	float x = u * (_width - 1);
	float y = v * (_height - 1);

	int x0 = static_cast<int>(std::floor(x));
	int x1 = std::min(x0 + 1, _width - 1);
	int y0 = static_cast<int>(std::floor(y));
	int y1 = std::min(y0 + 1, _height - 1);
	float tx = x - x0;
	float ty = y - y0;

	Vec3 c00 = _texels[y0 * _width + x0];
	Vec3 c10 = _texels[y0 * _width + x1];
	Vec3 c01 = _texels[y1 * _width + x0];
	Vec3 c11 = _texels[y1 * _width + x1];

	Vec3 c0 = c00 * (1.0f - tx) + c10 * tx;
	Vec3 c1 = c01 * (1.0f - tx) + c11 * tx;
	Vec3 final = c0 * (1.0f - ty) + c1 * ty;
	return (final);
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

bool	ImageTexture::_detectLinear(const std::string &filename)
{
	std::string lowercase = filename;
	std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(), ::tolower);
	if (lowercase.find("normal") != std::string::npos)
		return (true);
	return (false);
}
