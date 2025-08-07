#include "../inc/Sphere.hpp"

Sphere::Sphere(float radius, Vec3 center, BlinnPhongMaterial &mat)
	: AHittable(SPHERE, center), _radius(radius), _mat(mat)
{
}

Sphere::Sphere(const Sphere &other)
	: AHittable(SPHERE, other._pos), _radius(other._radius), _mat(other._mat)
{
}

Sphere&	Sphere::operator=(const Sphere &other)
{
	_pos = other._pos;
	_radius = other._radius;
	_mat = other._mat;
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
		return (Hit(NAN, Vec3(0, 0, 0), Vec3(0, 0, 0)));

	float t1 = (b - sqrtf(discriminant)) / a;
	float t2 = (b + sqrtf(discriminant)) / a;
	if (t1 >= 0)
	{
		Vec3 hit_point = rayAt(ray, t1);
		return (Hit(t1, (hit_point - _pos).normalize(), hit_point));
	}
	else if (t2 >= 0)
	{
		Vec3 hit_point = rayAt(ray, t2);
		return (Hit(t2, ((hit_point - _pos).normalize()) * -1, hit_point));
	}
	else
		return (Hit(NAN, Vec3(0, 0, 0), Vec3(0, 0, 0)));
}

float	Sphere::getRadius(void) const
{
	return (_radius);
}

BlinnPhongMaterial&	Sphere::getMat(void) const
{
	return (_mat);
}

std::ostream	&operator<<(std::ostream &os, const Sphere &sp)
{
	std::cout << "Sphere, radius: " << sp.getRadius() << ", center: " << sp.getPos();
	return (os);
}
