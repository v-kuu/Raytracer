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

	HitRecord ret(miss);
	Vec3	oc = _pos - ray.orig;
	float	a = dot(ray.dir, ray.dir);
	float	b = dot(ray.dir, oc);
	float	c = dot(oc, oc) - _radius * _radius;
	float	discriminant = b * b - a * c;
	if (discriminant < 0)
		return (ret);
	float disc_square = sqrtf(discriminant);
	float t1 = (b - disc_square) / a;
	float t2 = (b + disc_square) / a;

	auto calculate_hit = [&](float t, bool inside)
	{
		ret.t = t;
		ret.point = rayAt(ray, t);
		ret.normal = (ret.point - _pos).normalize();
		float theta = std::acos(-ret.normal.y);
		float phi = std::atan2(-ret.normal.z, ret.normal.x) + M_PI;
		ret.u = phi / (2 * M_PI);
		ret.v = theta / M_PI;
		if (inside)
			ret.normal = ret.normal * -1;
		ret.tangent = cross(Vec3(0, 1, 0), ret.normal).normalize();
		if (ret.tangent.length() < 1e-6)
			ret.tangent = cross(Vec3(1, 0, 0), ret.normal).normalize();
		ret.bitangent = cross(ret.tangent, ret.normal).normalize();
		ret.mat = _mat;
		return (ret);
	};
	if (t1 >= 0)
		return (calculate_hit(t1, false));
	else if (t2 >= 0)
		return (calculate_hit(t2, true));
	else
		return (ret);
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
