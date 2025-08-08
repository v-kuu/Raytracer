#pragma once
#include "ALight.hpp"

class	PointLight : public ALight
{
	public:
		PointLight(void) = delete;
		PointLight(float r, float g, float b, float intensity, Vec3 pos);
};
