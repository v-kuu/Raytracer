#include "../inc/ALight.hpp"

ALight::ALight(float red, float green, float blue, float intensity, const Vec3 &pos)
	: _color(red, green, blue), _pos(pos), _intensity(intensity)
{
	if (_intensity < 0 || _intensity > 1)
		throw (std::runtime_error("Color intensity out of bounds (0 <-> 1)"));
}

Vec3	ALight::getColor(void) const
{
	return (_color);
}

Vec3	ALight::getPos(void) const
{
	return (_pos);
}

float	ALight::getIntensity(void) const
{
	return (_intensity);
}
