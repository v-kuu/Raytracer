#include "../inc/Sphere.hpp"

Sphere::Sphere(float radius, Vec3 center)
	: AHittable(SPHERE, center), _radius(radius)
{
}

Sphere::Sphere(const Sphere &other)
	: AHittable(SPHERE, other._pos), _radius(other._radius)
{
}

Sphere&	Sphere::operator=(const Sphere &other)
{
	_pos = other._pos;
	_radius = other._radius;
	return (*this);
}

AHittable::Hit	Sphere::detectHit(Ray ray)
{
	Vec3	oc = _pos - ray.orig;
	float	a = dot(ray.dir, ray.dir);
	float	b = dot(ray.dir, oc);
	float	c = dot(oc, oc) - _radius * _radius;
	float	discriminant = b * b - a * c;
	if (discriminant < 0)
		return (Hit(NAN, Vec3(0, 0, 0)));

	float t1 = (b - sqrtf(discriminant)) / a;
	float t2 = (b + sqrtf(discriminant)) / a;
	if (t1 >= 0)
		return (Hit(t1, (_pos - rayAt(ray, t1)).normalize()));
	else if (t2 >= 0)
		return (Hit(t2, (_pos - rayAt(ray, t2)).normalize()));
	else
		return (Hit(NAN, Vec3(0, 0, 0)));
}
