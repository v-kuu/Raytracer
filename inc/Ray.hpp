#pragma once
#include "Vec3.hpp"
#include <iostream>

struct	Ray
{
	Vec3	orig;
	Vec3	dir;

	Ray(const Vec3 &origin, const Vec3 &direction);
};

std::ostream	&operator<<(std::ostream &os, const Ray &ray);

Vec3	rayAt(const Ray &ray, float t);
