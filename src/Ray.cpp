#include "../inc/Ray.hpp"

Ray::Ray(Vec3 origin, Vec3 direction) : orig(origin), dir(direction)
{
}

Vec3	rayAt(Ray ray, float t)
{
	return ((ray.dir * t) + ray.orig);
}
