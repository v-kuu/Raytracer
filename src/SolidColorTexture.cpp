#include "../inc/SolidColorTexture.hpp"

SolidColorTexture::SolidColorTexture(float r, float g, float b) : _color(r, g, b)
{
}

Vec3	SolidColorTexture::lookup(float u, float v, const Vec3 &point)
{
	(void)u;
	(void)v;
	(void)point;
	return (_color);
}
