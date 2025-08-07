#pragma once
#include "AHittable.hpp"
#include "BlinnPhongMaterial.hpp"

class	Sphere : public AHittable
{
	public:
		Sphere(void) = delete;
		Sphere(float radius, Vec3 center, BlinnPhongMaterial &mat);
		~Sphere(void) = default;
		Sphere(const Sphere &other);
		Sphere	&operator=(const Sphere &other);

		Hit	detectHit(Ray ray) override;

		float				getRadius(void) const;
		BlinnPhongMaterial	&getMat(void) const;

	private:
		float				_radius;
		BlinnPhongMaterial	&_mat;
};

std::ostream	&operator<<(std::ostream &os, const Sphere &sp);
