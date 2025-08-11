#include "../inc/Sphere.hpp"

Sphere::Sphere(float radius, Vec3 center, IMaterial *mat)
	: AHittable(SPHERE, center, mat), _radius(radius)
{
}

Sphere::~Sphere(void)
{
	delete _mat;
}

Sphere::Sphere(const Sphere &other)
	: AHittable(SPHERE, other._pos, other._mat), _radius(other._radius)
{
}

Sphere&	Sphere::operator=(const Sphere &other)
{
	_pos = other._pos;
	_radius = other._radius;
	_mat = other._mat;
	return (*this);
}

HitRecord	Sphere::detectHit(Ray &ray)
{
	Vec3	oc = _pos - ray.orig;
	float	a = dot(ray.dir, ray.dir);
	float	b = dot(ray.dir, oc);
	float	c = dot(oc, oc) - _radius * _radius;
	float	discriminant = b * b - a * c;
	if (discriminant < 0)
		return (HitRecord(NAN, Vec3(0, 0, 0), Vec3(0, 0, 0)));

	float t1 = (b - sqrtf(discriminant)) / a;
	float t2 = (b + sqrtf(discriminant)) / a;
	if (t1 >= 0)
	{
		Vec3 hit_point = rayAt(ray, t1);
		return (HitRecord(t1, (hit_point - _pos).normalize(), hit_point));
	}
	else if (t2 >= 0)
	{
		Vec3 hit_point = rayAt(ray, t2);
		return (HitRecord(t2, ((hit_point - _pos).normalize()) * -1, hit_point));
	}
	else
		return (HitRecord(NAN, Vec3(0, 0, 0), Vec3(0, 0, 0)));
}

float	Sphere::getRadius(void) const
{
	return (_radius);
}

std::ostream	&operator<<(std::ostream &os, const Sphere &sp)
{
	os << "Sphere, radius: " << sp.getRadius() << ", center: " << sp.getPos();
	return (os);
}
