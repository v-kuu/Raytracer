#pragma once
#include "Vec3.hpp"
#include "Ray.hpp"
#include "IMaterial.hpp"
#include "HitRecord.hpp"
#include "AABB.hpp"

enum	e_hit_type
{
	SPHERE
};

class	IMaterial;
struct	HitRecord;

class	AHittable
{
	public:
		AHittable(void) = delete;
		AHittable(int type, const Vec3 &pos, std::shared_ptr<IMaterial> mat);
		virtual ~AHittable(void) = default;

		virtual HitRecord	detectHit(const Ray &ray) = 0;
		virtual AABB		boundingBox(void) const = 0;

		Vec3						getPos(void) const;
		int							getType(void) const;
		std::shared_ptr<IMaterial>	getMat(void) const;

	protected:
		Vec3						_pos;
		int							_type;
		std::shared_ptr<IMaterial>	_mat;
};
