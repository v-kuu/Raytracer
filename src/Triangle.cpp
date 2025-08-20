#include "../inc/Triangle.hpp"

Triangle::Triangle(const Vec3 &p0, const Vec3 &p1, const Vec3 &p2, std::shared_ptr<IMaterial> mat) : AHittable(p0, mat), _pos1(p1), _pos2(p2)
{
}

Triangle::Triangle(const Triangle &other)
	: AHittable(other._pos, other._mat), _pos1(other._pos1), _pos2(other._pos2)
{
}

Triangle&	Triangle::operator=(const Triangle &other)
{
	_pos = other._pos;
	_mat = other._mat;
	_pos1 = other._pos1;
	_pos2 = other._pos2;
	return (*this);
}

HitRecord	Triangle::detectHit(const Ray &ray)
{
	constexpr float miss = std::numeric_limits<float>::max();

	Vec3 edge1 = _pos1 - _pos;
	Vec3 edge2 = _pos2 - _pos;
	Vec3 rop0 = ray.orig - _pos;
	Vec3 normal = cross(edge1, edge2);
	Vec3 q = cross(rop0, ray.dir);
	float det = 1.0 / dot(ray.dir, normal);
	float u = det * dot(q * -1, edge2);
	float v = det * dot(q, edge1);
	float t = det * dot(normal * -1, rop0);
	if (std::min(u ,v) < 0.0 || (u + v) > 1.0)
		return (HitRecord(miss));
	normal = normal.normalize();
	if (dot(normal, ray.dir) > 0)
		normal = normal * -1;
	return (HitRecord(t, normal, rayAt(ray, t), _mat, u, v));
}

AABB	Triangle::boundingBox(void) const
{
	AABB volume;
	volume.extend(_pos);
	volume.extend(_pos1);
	volume.extend(_pos2);
	return (volume);
}
