#pragma once
#include "Vec3.hpp"
#include "Ray.hpp"

struct	AABB
{
	Vec3	min;
	Vec3	max;

	AABB(void) = default;
	AABB(Vec3 min, Vec3 max);
	AABB(const AABB &box1, const AABB &box2);

	bool	intersect(const Ray &ray) const;
};
