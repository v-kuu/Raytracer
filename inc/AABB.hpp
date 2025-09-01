#pragma once
#include "Vec3.hpp"
#include "Ray.hpp"

struct	AABB
{
	Vec3	min;
	Vec3	max;

	AABB(void);

	bool	operator<(const AABB &other) const;

	void	extend(const AABB &other);
	void	extend(const Vec3 &point);
	Vec3	center(void) const;
	float	surfaceArea(void) const;
	bool	intersect(const Ray &ray) const;
};
