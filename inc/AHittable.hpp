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

class	AHittable
{
	public:
		AHittable(void) = delete;
		AHittable(int type, Vec3 pos, IMaterial *mat);
		virtual ~AHittable(void) = default;

		virtual HitRecord	detectHit(const Ray &ray) = 0;
		virtual AABB		boundingBox(void) const = 0;

		Vec3		getPos(void) const;
		int			getType(void) const;
		IMaterial	*getMat(void) const;

	protected:
		Vec3		_pos;
		int			_type;
		IMaterial	*_mat;
};
