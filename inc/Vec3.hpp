#pragma once
#include <math.h>
#include <iostream>

struct	Vec3
{
	float x;
	float y;
	float z;

	Vec3(void);
	Vec3(float xi, float yi, float zi);

	Vec3	operator+(const Vec3 &other) const;
	Vec3	operator-(const Vec3 &other) const;
	Vec3	operator*(float scalar) const;
	Vec3	operator/(float scalar) const;

	float	length(void) const;
	Vec3	normalize(void) const;
};

std::ostream	&operator<<(std::ostream &os, const Vec3 &vec);

float	dot(const Vec3 &lhs, const Vec3 &rhs);
Vec3	cross(const Vec3 &lhs, const Vec3 &rhs);
