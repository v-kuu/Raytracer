#include "../inc/Triangle.hpp"

Triangle::Triangle(const Vec3 &p0, const Vec3 &p1, const Vec3 &p2, std::shared_ptr<IMaterial> mat) :
	AHittable(p0, mat), _pos1(p1), _pos2(p2), _uv0(0.0f, 0.0f), _uv1(1.0f, 0.0f), _uv2(0.0f, 1.0f)
{
}

Triangle::Triangle(const Triangle &other)
	: AHittable(other._pos, other._mat), _pos1(other._pos1), _pos2(other._pos2),
	_uv0(other._uv0), _uv1(other._uv1), _uv2(other._uv2)
{
}

Triangle&	Triangle::operator=(const Triangle &other)
{
	_pos = other._pos;
	_mat = other._mat;
	_pos1 = other._pos1;
	_pos2 = other._pos2;
	_uv0 = other._uv0;
	_uv1 = other._uv1;
	_uv2 = other._uv2;
	return (*this);
}

HitRecord	Triangle::detectHit(const Ray &ray)
{
	constexpr float miss = std::numeric_limits<float>::max();

	HitRecord ret(miss);
	Vec3 edge1 = _pos1 - _pos;
	Vec3 edge2 = _pos2 - _pos;
	Vec3 rop0 = ray.orig - _pos;
	ret.normal = cross(edge1, edge2);
	Vec3 q = cross(rop0, ray.dir);
	float det = 1.0 / dot(ray.dir, ret.normal);
	ret.u = det * dot(q * -1, edge2);
	ret.v = det * dot(q, edge1);
	ret.t = det * dot(ret.normal * -1, rop0);
	if (std::min(ret.u ,ret.v) < 0.0 || (ret.u + ret.v) > 1.0)
		return (HitRecord(miss));
	ret.normal = ret.normal.normalize();
	if (dot(ret.normal, ray.dir) > 0)
		ret.normal = ret.normal * -1;
	ret.point = rayAt(ray, ret.t);
	ret.mat = _mat;

	Vec2 delta_uv1 = _uv1 - _uv0;
	Vec2 delta_uv2 = _uv2 - _uv0;
	float r = 1.0f / (delta_uv1.x * delta_uv2.y - delta_uv1.y * delta_uv2.x);
	ret.tangent = (edge1 * delta_uv2.y - edge2 * delta_uv1.y) * r;
	ret.bitangent = (edge2 * delta_uv1.x - edge1 * delta_uv2.x) * r;
	ret.tangent = ret.tangent.normalize();
	ret.bitangent = ret.bitangent.normalize();
	return (ret);
}

AABB	Triangle::boundingBox(void) const
{
	AABB volume;
	volume.extend(_pos);
	volume.extend(_pos1);
	volume.extend(_pos2);
	return (volume);
}
