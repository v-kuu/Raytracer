#include "../inc/BlinnPhongMaterial.hpp"

float BlinnPhongMaterial::_shininess = 32.0f;

BlinnPhongMaterial::BlinnPhongMaterial(float r, float g, float b)
	: _red(r), _green(g), _blue(b)
{
}

BlinnPhongMaterial::BlinnPhongMaterial(const BlinnPhongMaterial &other)
	: _red(other._red), _green(other._green), _blue(other._blue)
{
}

BlinnPhongMaterial&	BlinnPhongMaterial::operator=(const BlinnPhongMaterial &other)
{
	if (this == &other)
		return (*this);
	_red = other._red;
	_green = other._green;
	_blue = other._blue;
	return (*this);
}

Uint32	BlinnPhongMaterial::shade(const Ray &ray, const AHittable::Hit &hit,
		const PointLight &l)
{
	Vec3 light_dir = (l.getPos() - hit.point).normalize();
	Vec3 view_dir = (ray.dir * -1).normalize();
	Vec3 halfway = (light_dir + view_dir).normalize();
	float spec = powf(fmax(dot(hit.normal, halfway), 0.0f), _shininess);
	return (static_cast<Uint8>(_red * spec) << 24
			| static_cast<Uint8>(_green * spec) << 16
			| static_cast<Uint8>(_blue * spec) << 8
			| 0xFF);
}
