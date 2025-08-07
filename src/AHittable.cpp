#include "../inc/AHittable.hpp"

AHittable::AHittable(int type, Vec3 pos) : _type(type), _pos(pos)
{
}

AHittable::Hit::Hit(float t, Vec3 normal, Vec3 point)
	: t(t), normal(normal), point(point)
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
