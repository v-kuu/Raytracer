#pragma once
#include <SDL3/SDL.h>
#include "Ray.hpp"
#include "HitRecord.hpp"

class	Scene;
struct	HitRecord;
struct	Ray;

class	IMaterial
{
	public:
		virtual ~IMaterial(void) {};

		virtual Uint32	shade(const Ray &ray, const HitRecord &hit, const Scene &sc) const = 0;
};
