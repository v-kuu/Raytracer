#include "../inc/AHittable.hpp"

AHittable::AHittable(int type, Vec3 pos, IMaterial *mat) : _pos(pos), _type(type), _mat(mat)
{
}

Vec3	AHittable::getPos(void) const
{
	return (_pos);
}

int		AHittable::getType(void) const
{
	return (_type);
}

IMaterial*	AHittable::getMat(void) const
{
	return (_mat);
}
