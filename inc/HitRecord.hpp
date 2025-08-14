#pragma once
#include "Vec3.hpp"
#include "IMaterial.hpp"

class	IMaterial;

struct	HitRecord
{
	float						t;
	Vec3						normal;
	Vec3						point;
	std::shared_ptr<IMaterial>	mat;

	HitRecord(float t);
	HitRecord(float t, Vec3 normal, Vec3 point, std::shared_ptr<IMaterial> mat);
};
