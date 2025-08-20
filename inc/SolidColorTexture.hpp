#pragma once
#include "ITexture.hpp"
#include <algorithm>

class	SolidColorTexture : public ITexture
{
	public:
		SolidColorTexture(float r, float g, float b);

		Vec3	lookup(float u, float v, const Vec3 &point) override;

	private:
		Vec3	_color;
};
