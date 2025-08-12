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

		virtual HitRecord	detectHit(Ray &ray) = 0;

		const AABB	&getBoundingBox(void) const;
		Vec3		getPos(void) const;
		int			getType(void) const;
		IMaterial	*getMat(void) const;

	protected:
		AABB		_bounding_box;
		Vec3		_pos;
		int			_type;
		IMaterial	*_mat;
};
