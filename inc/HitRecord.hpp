#pragma once
#include <memory>
#include "Vec3.hpp"

class	IMaterial;

struct	HitRecord
{
	float						t;
	Vec3						normal;
	Vec3						point;
	std::shared_ptr<IMaterial>	mat;

	HitRecord(float t);
	HitRecord(float t, const Vec3 &normal, const Vec3 &point, std::shared_ptr<IMaterial> mat);
};
