#pragma once
#include <SDL3/SDL.h>
#include "Ray.hpp"
#include "Scene.hpp"
#include "HitRecord.hpp"

class	Scene;
class	AHittable;

class	IMaterial
{
	public:
		virtual ~IMaterial(void) {};

		virtual Uint32	shade(const Ray &ray, const HitRecord &hit, const Scene &sc) = 0;
};
