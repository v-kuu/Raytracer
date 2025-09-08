#include "../inc/Sphere.hpp"

Sphere::Sphere(float radius, const Vec3 &center, std::shared_ptr<IMaterial> mat)
	: AHittable(center, mat), _radius(radius)
{
}

Sphere::Sphere(const Sphere &other)
	: AHittable(other._pos, other._mat), _radius(other._radius)
{
}

Sphere&	Sphere::operator=(const Sphere &other)
{
	_pos = other._pos;
	_radius = other._radius;
	_mat = other._mat;
	return (*this);
}

AABB	Sphere::boundingBox(void) const
{
	Vec3 radius_vec(_radius, _radius, _radius);
	AABB volume;
	volume.extend(_pos - radius_vec);
	volume.extend(_pos + radius_vec);
	return (volume);
}

HitRecord	Sphere::detectHit(const Ray &ray)
{
	constexpr float miss = std::numeric_limits<float>::max();

	Vec3	oc = _pos - ray.orig;
	float	a = dot(ray.dir, ray.dir);
	float	b = dot(ray.dir, oc);
	float	c = dot(oc, oc) - _radius * _radius;
	float	discriminant = b * b - a * c;
	if (discriminant < 0)
		return (HitRecord(miss));
	float disc_square = sqrtf(discriminant);
	float t1 = (b - disc_square) / a;
	float t2 = (b + disc_square) / a;
	if (t1 >= 0)
	{
		Vec3 hit_point = rayAt(ray, t1);
		Vec3 local_p = (hit_point - _pos).normalize();
		float theta = std::acos(-local_p.y);
		float phi = std::atan2(-local_p.z, local_p.x) + M_PI;
		float u = phi / (2 * M_PI);
		float v = theta / M_PI;
		return (HitRecord(t1, (hit_point - _pos).normalize(), hit_point, _mat, u, v));
	}
	else if (t2 >= 0)
	{
		Vec3 hit_point = rayAt(ray, t2);
		Vec3 local_p = (hit_point - _pos).normalize();
		float theta = std::acos(-local_p.y);
		float phi = std::atan2(-local_p.z, local_p.x) + M_PI;
		float u = phi / (2 * M_PI);
		float v = theta / M_PI;
		return (HitRecord(t2, ((hit_point - _pos).normalize()) * -1, hit_point, _mat, u, v));
	}
	else
		return (HitRecord(miss));
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
