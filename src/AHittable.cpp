#include "../inc/AHittable.hpp"

AHittable::AHittable(const Vec3 &pos, std::shared_ptr<IMaterial> mat) : _pos(pos), _mat(mat)
{
}

Vec3	AHittable::getPos(void) const
{
	return (_pos);
}

std::shared_ptr<IMaterial>	AHittable::getMat(void) const
{
	return (_mat);
}
