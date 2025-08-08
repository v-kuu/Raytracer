#include "../inc/AHittable.hpp"

AHittable::AHittable(int type, Vec3 pos, IMaterial *mat) : _type(type), _pos(pos), _mat(mat)
{
}

int		AHittable::getType(void) const
{
	return (_type);
}

Vec3	AHittable::getPos(void) const
{
	return (_pos);
}

IMaterial*	AHittable::getMat(void) const
{
	return (_mat);
}
