#include "../inc/PointLight.hpp"

PointLight::PointLight(float r, float g, float b, float intensity, Vec3 pos)
	: ALight(r, g, b, intensity), _pos(pos)
{
}

Vec3	PointLight::getPos(void) const
{
	return (_pos);
}
