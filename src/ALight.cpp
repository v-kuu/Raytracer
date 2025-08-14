#include "../inc/ALight.hpp"

ALight::ALight(float red, float green, float blue, float intensity, const Vec3 &pos)
	: _red(red), _green(green), _blue(blue), _intensity(intensity), _pos(pos)
{
	if (_intensity < 0 || _intensity > 1)
		throw (std::runtime_error("Color intensity out of bounds (0 <-> 1)"));
}

float	ALight::getRed(void) const
{
	return (_red);
}

float	ALight::getGreen(void) const
{
	return (_green);
}

float	ALight::getBlue(void) const
{
	return (_blue);
}

float	ALight::getIntensity(void) const
{
	return (_intensity);
}

Vec3	ALight::getPos(void) const
{
	return (_pos);
}
