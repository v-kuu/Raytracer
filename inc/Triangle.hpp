#pragma once
#include "AHittable.hpp"

class	Triangle : public AHittable
{
	public:
		Triangle(void) = delete;
		Triangle(const Vec3 &p0, const Vec3 &p1, const Vec3 &p2, std::shared_ptr<IMaterial> mat);
		~Triangle(void) = default;
		Triangle(const Triangle &other);
		Triangle	&operator=(const Triangle &other);

		HitRecord	detectHit(const Ray &ray) override;
		AABB		boundingBox(void) const override;

	private:
		Vec3	_pos1;
		Vec3	_pos2;
};
