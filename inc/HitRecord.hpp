#pragma once
#include <memory>
#include "Vec3.hpp"

class	IMaterial;

struct	HitRecord
{
	Vec3						normal;
	Vec3						point;
	Vec3						tangent;
	Vec3						bitangent;
	std::shared_ptr<IMaterial>	mat;
	float						t;
	float						u;
	float						v;

	HitRecord(float t);
};
