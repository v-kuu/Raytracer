#pragma once
#include "Vec3.hpp"
#include "Ray.hpp"

enum	e_hit_type
{
	SPHERE
};

class	AHittable
{
	public:
		AHittable(void) = delete;
		AHittable(int type, Vec3 pos);
		virtual ~AHittable(void) = default;

		struct	Hit
		{
			float	t;
			Vec3	normal;
		};
		virtual Hit	detectHit(Ray ray) = 0;

		int		getType(void) const;
		Vec3	getPos(void) const;

	protected:
		int		_type;
		Vec3	_pos;
};
