#include "../inc/AABB.hpp"

AABB::AABB(Vec3 min, Vec3 max) : min(min), max(max)
{
}

AABB::AABB(const AABB &box1, const AABB &box2)
{
	min.x = std::min(box1.min.x, box2.min.x);
	min.y = std::min(box1.min.y, box2.min.y);
	min.z = std::min(box1.min.z, box2.min.z);

	max.x = std::max(box1.max.x, box2.max.x);
	max.y = std::max(box1.max.y, box2.max.y);
	max.z = std::max(box1.max.z, box2.max.z);
}

//Andrew Woo's 1990 algorithm optimized by Pierre Terdiman in 2000
bool	AABB::intersect(const Ray &ray) const
{
	bool inside = true;
	Vec3 MaxT(-1.0f, -1.0f, -1.0f);

	for (int i = 0; i < 3; ++i)
	{
		if (ray.orig[i] < min[i])
		{
			inside = false;
			if (ray.dir[i])
				MaxT[i] = (min[i] - ray.orig[i]) / ray.dir[i];
		}
		else if (ray.orig[i] > max[i])
		{
			inside = false;
			if (ray.dir[i])
				MaxT[i] = (max[i] - ray.orig[i]) / ray.dir[i];
		}
	}
	if (inside)
		return (true);

	int WhichPlane = 0;
	if (MaxT[1] > MaxT[WhichPlane])
		WhichPlane = 1;
	if (MaxT[2] > MaxT[WhichPlane])
		WhichPlane = 2;
	if (MaxT[WhichPlane] < 0)
		return (false);

	Vec3 HitP;
	for (int i = 0; i < 3; ++i)
	{
		if (i != WhichPlane)
		{
			HitP[i] = ray.orig[i] + MaxT[WhichPlane] * ray.dir[i];
			if (HitP[i] < min[i] - 0.00001f || HitP[i] > max[i] + 0.00001f)
				return (false);
		}
	}
	return (true);
}
