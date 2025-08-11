#pragma once
#include "Vec3.hpp"
#include <cmath>

struct	Quaternion
{
	float w;
	float x;
	float y;
	float z;

	Quaternion(void);
	Quaternion(float w, float x, float y, float z);
	Quaternion(float angle_deg, Vec3 axis);
	Quaternion(Vec3 from, Vec3 to);

	Quaternion	operator*(const Quaternion &other) const;
	bool		operator==(const Quaternion &other) const;

	Vec3		rotate(const Vec3 &vec) const;
	float		length(void) const;
	Quaternion	normalize(void) const;
	Quaternion	inverse(void) const;
};

std::ostream	&operator<<(std::ostream &os, const Quaternion quat);
