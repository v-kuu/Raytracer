#pragma once
#include "Vec3.hpp"

struct	Ray
{
	Vec3	orig;
	Vec3	dir;

	Ray(Vec3 origin, Vec3 direction);
};

Vec3	rayAt(Ray ray, float t);
