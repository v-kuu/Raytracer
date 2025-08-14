#pragma once
#include "AHittable.hpp"

class	Sphere : public AHittable
{
	public:
		Sphere(void) = delete;
		Sphere(float radius, const Vec3 &center, std::shared_ptr<IMaterial> mat);
		~Sphere(void) = default;
		Sphere(const Sphere &other);
		Sphere	&operator=(const Sphere &other);

		HitRecord	detectHit(const Ray &ray) override;
		AABB		boundingBox(void) const override;

		float	getRadius(void) const;

	private:
		float	_radius;
};

std::ostream	&operator<<(std::ostream &os, const Sphere &sp);
