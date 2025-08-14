#include "../inc/AHittable.hpp"

AHittable::AHittable(int type, const Vec3 &pos, std::shared_ptr<IMaterial> mat) : _pos(pos), _type(type), _mat(mat)
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

std::shared_ptr<IMaterial>	AHittable::getMat(void) const
{
	return (_mat);
}
