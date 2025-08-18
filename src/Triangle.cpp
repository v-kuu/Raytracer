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

//Möller-Trumbore
HitRecord	Triangle::detectHit(const Ray &ray)
{
	constexpr float epsilon = std::numeric_limits<float>::epsilon();
	constexpr float miss = std::numeric_limits<float>::max();

	Vec3 edge1 = _pos1 - _pos;
	Vec3 edge2 = _pos2 - _pos;
	Vec3 cross_r_e2 = cross(ray.dir, edge2);
	float det = dot(edge1, cross_r_e2);
	if (det > -epsilon && det < epsilon)
		return (HitRecord(miss));
	float det_inv = 1.0 / det;
	Vec3 rop0 = ray.orig - _pos;
	float u = det_inv * dot(rop0, cross_r_e2);
	if (u < 0 || u > 1.0f)
		return (HitRecord(miss));
	Vec3 cross_rop0_e1 = cross(rop0, edge1);
	float v = det_inv * dot(ray.dir, cross_rop0_e1);
	if (v < 0 || v > 1.0f)
		return (HitRecord(miss));
	float t = det_inv * dot(edge2, cross_rop0_e1);
	if (t <= epsilon)
		return (HitRecord(miss));
	Vec3 normal = cross(edge1, edge2).normalize();
	if (dot(normal, ray.dir) > 0)
		normal = normal * -1;
	return (HitRecord(t, normal, rayAt(ray, t), _mat));
}

AABB	Triangle::boundingBox(void) const
{
	AABB volume;
	volume.extend(_pos);
	volume.extend(_pos1);
	volume.extend(_pos2);
	return (volume);
}
