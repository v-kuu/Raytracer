#pragma once
#include "Vec3.hpp"
#include <stdexcept>

class	ALight
{
	public:
		ALight(void) = delete;
		ALight(float red, float green, float blue, float intensity, const Vec3 &pos);
		virtual	~ALight(void) = default;

		Vec3	getColor(void) const;
		Vec3	getPos(void) const;
		float	getIntensity(void) const;

	protected:
		Vec3	_color;
		Vec3	_pos;
		float	_intensity;
};
