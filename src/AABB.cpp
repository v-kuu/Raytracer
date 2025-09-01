#include "../inc/AABB.hpp"

AABB::AABB(void)
	: min(std::numeric_limits<float>::max(),
			std::numeric_limits<float>::max(),
			std::numeric_limits<float>::max()),
	max(std::numeric_limits<float>::min(),
			std::numeric_limits<float>::min(),
			std::numeric_limits<float>::min())
{
}

bool	AABB::operator<(const AABB &other) const
{
	return (center().x < other.center().x);
}

void	AABB::extend(const AABB &other)
{
	min.x = std::min(min.x, other.min.x);
	min.y = std::min(min.y, other.min.y);
	min.z = std::min(min.z, other.min.z);

	max.x = std::max(max.x, other.max.x);
	max.y = std::max(max.y, other.max.y);
	max.z = std::max(max.z, other.max.z);
}

void	AABB::extend(const Vec3 &point)
{
	min.x = std::min(min.x, point.x);
	min.y = std::min(min.y, point.y);
	min.z = std::min(min.z, point.z);

	max.x = std::max(max.x, point.x);
	max.y = std::max(max.y, point.y);
	max.z = std::max(max.z, point.z);
}

Vec3	AABB::center(void) const
{
	Vec3 ret((min.x + max.x) / 2,
			(min.y + max.y) / 2,
			(min.z + max.z) / 2);
	return (ret);
}

float	AABB::surfaceArea(void) const
{
	Vec3 size = max - min;
	return (2.0f * (
			size.x * size.y +
			size.x * size.z +
			size.y * size.z));
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
			if (ray.dir[i] != 0)
				MaxT[i] = (min[i] - ray.orig[i]) / ray.dir[i];
		}
		else if (ray.orig[i] > max[i])
		{
			inside = false;
			if (ray.dir[i] != 0)
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
