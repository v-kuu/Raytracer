#pragma once
#include <math.h>
#include <iostream>

struct	Vec2
{
	float x;
	float y;

	Vec2(void);
	Vec2(float x, float y);

	Vec2			operator+(const Vec2 &other) const;
	Vec2			operator-(const Vec2 &other) const;
	Vec2			operator*(float scalar) const;
	Vec2			operator*(const Vec2 &other) const;
	Vec2			operator/(float scalar) const;
	float			&operator[](unsigned int i);
	const float		&operator[](unsigned int i) const;

	float	length(void) const;
	Vec2	normalize(void) const;
};

std::ostream	&operator<<(std::ostream &os, const Vec2 &vec);
