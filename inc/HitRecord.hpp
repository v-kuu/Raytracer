#pragma once
#include "Vec3.hpp"

struct	HitRecord
{
	float		t;
	Vec3		normal;
	Vec3		point;

	HitRecord(float t, Vec3 normal, Vec3 point);
};
