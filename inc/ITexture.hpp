#pragma once
#include <SDL3/SDL.h>
#include "Vec3.hpp"

class	ITexture
{
	public:
		virtual ~ITexture(void) = default;

		virtual Vec3	lookup(float u, float v, const Vec3 &point) = 0;
};
