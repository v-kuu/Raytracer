#pragma once
#include "Vec3.hpp"
#include "Ray.hpp"
#include "IMaterial.hpp"
#include "HitRecord.hpp"

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

		int			getType(void) const;
		Vec3		getPos(void) const;
		IMaterial	*getMat(void) const;

	protected:
		int					_type;
		Vec3				_pos;
		IMaterial			*_mat;
};
