#pragma once
#include <SDL3/SDL.h>
#include "Ray.hpp"
#include "AHittable.hpp"
#include "PointLight.hpp"

class	IMaterial
{
	public:
		virtual ~IMaterial(void) {};

		virtual Uint32	shade(const Ray &ray, const AHittable::Hit &hit, const PointLight &l) = 0;
};
