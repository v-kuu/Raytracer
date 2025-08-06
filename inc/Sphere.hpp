#pragma once
#include "AHittable.hpp"

class	Sphere : public AHittable
{
	public:
		Sphere(void) = delete;
		Sphere(float radius, Vec3 center);
		~Sphere(void) = default;
		Sphere(const Sphere &other);
		Sphere	&operator=(const Sphere &other);

		Hit	detectHit(Ray ray) override;

		float	getRadius(void) const;

	private:
		float	_radius;
};

std::ostream	&operator<<(std::ostream &os, const Sphere &sp);
