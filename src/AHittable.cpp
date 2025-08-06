#include "../inc/AHittable.hpp"

AHittable::AHittable(int type, Vec3 pos) : _type(type), _pos(pos)
{
}

AHittable::Hit::Hit(float t, Vec3 normal) : t(t), normal(normal)
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
