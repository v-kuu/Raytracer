#include "../inc/HitRecord.hpp"

HitRecord::HitRecord(float t) : t(t)
{
}

HitRecord::HitRecord(float t, const Vec3 &normal, const Vec3 &point, std::shared_ptr<IMaterial> mat, float u, float v)
	: normal(normal), point(point), mat(mat), t(t), u(u), v(v)
{
}
