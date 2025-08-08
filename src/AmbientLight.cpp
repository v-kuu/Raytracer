#include "../inc/AmbientLight.hpp"

AmbientLight::AmbientLight(float r, float g, float b, float intensity)
	: ALight(r, g, b, intensity, Vec3(0, 0, 0))
{
}
