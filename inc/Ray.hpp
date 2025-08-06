#pragma once
#include "Vec3.hpp"
#include <iostream>

struct	Ray
{
	Vec3	orig;
	Vec3	dir;

	Ray(Vec3 origin, Vec3 direction);
};

std::ostream	&operator<<(std::ostream &os, const Ray &ray);

Vec3	rayAt(Ray ray, float t);
