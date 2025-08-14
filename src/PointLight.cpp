#include "../inc/PointLight.hpp"

PointLight::PointLight(float r, float g, float b, float intensity, const Vec3 &pos)
	: ALight(r, g, b, intensity, pos)
{
}
