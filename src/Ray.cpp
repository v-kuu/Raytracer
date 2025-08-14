#include "../inc/Ray.hpp"

Ray::Ray(const Vec3 &origin, const Vec3 &direction) : orig(origin), dir(direction)
{
}

std::ostream	&operator<<(std::ostream &os, const Ray &ray)
{
	os << "Origin: " << ray.orig << ", Direction: " << ray.dir;
	return (os);
}

Vec3	rayAt(const Ray &ray, float t)
{
	return ((ray.dir * t) + ray.orig);
}
