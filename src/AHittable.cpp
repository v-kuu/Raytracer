#include "../inc/AHittable.hpp"

AHittable::AHittable(int type, Vec3 pos) : _type(type), _pos(pos)
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
