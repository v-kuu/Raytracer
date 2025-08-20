#pragma once
#include <memory>
#include "Vec3.hpp"

class	IMaterial;

struct	HitRecord
{
	Vec3						normal;
	Vec3						point;
	std::shared_ptr<IMaterial>	mat;
	float						t;
	float						u;
	float						v;

	HitRecord(float t);
	HitRecord(float t, const Vec3 &normal, const Vec3 &point, std::shared_ptr<IMaterial> mat, float u, float v);
};
