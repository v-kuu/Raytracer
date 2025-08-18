#pragma once
#include "Vec3.hpp"
#include "Ray.hpp"
#include "IMaterial.hpp"
#include "HitRecord.hpp"
#include "AABB.hpp"

class	IMaterial;
struct	HitRecord;

class	AHittable
{
	public:
		AHittable(void) = delete;
		AHittable(const Vec3 &pos, std::shared_ptr<IMaterial> mat);
		virtual ~AHittable(void) = default;

		virtual HitRecord	detectHit(const Ray &ray) = 0;
		virtual AABB		boundingBox(void) const = 0;

		Vec3						getPos(void) const;
		std::shared_ptr<IMaterial>	getMat(void) const;

	protected:
		Vec3						_pos;
		std::shared_ptr<IMaterial>	_mat;
};
