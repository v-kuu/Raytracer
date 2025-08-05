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
		AHittable(int type, Vec3 pos) : _type(type), _pos(pos){}
		virtual ~AHittable(void) = default;

		struct	Hit
		{
			float	t;
			Vec3	normal;
		};
		virtual Hit	detectHit(Ray ray) = 0;

	protected:
		int		_type;
		Vec3	_pos;
};
