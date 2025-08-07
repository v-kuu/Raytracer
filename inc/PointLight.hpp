#pragma once
#include "ALight.hpp"
#include "Vec3.hpp"

class	PointLight : public ALight
{
	public:
		PointLight(void) = delete;
		PointLight(float r, float g, float b, float intensity, Vec3 pos);

		Vec3	getPos(void) const;

	private:
		Vec3	_pos;
};
