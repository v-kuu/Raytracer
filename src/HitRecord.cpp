#include "../inc/HitRecord.hpp"

HitRecord::HitRecord(float t) : t(t)
{
}

HitRecord::HitRecord(float t, Vec3 normal, Vec3 point, std::shared_ptr<IMaterial> mat)
	: t(t), normal(normal), point(point), mat(mat)
{
}
