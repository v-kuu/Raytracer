#include "../inc/BlinnPhongMaterial.hpp"

float			BlinnPhongMaterial::_shininess = 32.0f;
AmbientLight	BlinnPhongMaterial::_a = AmbientLight(1.0f, 1.0f, 1.0f, 0.2);

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

Uint32	BlinnPhongMaterial::shade(const Ray &ray, const HitRecord &hit, const Scene &sc)
{
	float ambient[3] = { _red * _a.getRed() * _a.getIntensity(),
						_green * _a.getGreen() * _a.getIntensity(),
						_blue * _a.getBlue() * _a.getIntensity() };

	std::shared_ptr<ALight> l = sc.getLights()[0];
	Vec3 light_dir = (l->getPos() - hit.point).normalize();
	float light_distance = (l->getPos() - hit.point).length();
	Vec3 shadow_orig(hit.point + hit.normal * 1e-4);
	Ray shadow_ray(shadow_orig, light_dir);

	HitRecord shadow = sc.getBVH()->intersect(shadow_ray);
	if (shadow.t >= 0 && shadow.t < light_distance)
	{
		Uint8 red = static_cast<Uint8>(255 *
				std::clamp(ambient[0], 0.0f, 1.0f));
		Uint8 green = static_cast<Uint8>(255 *
				std::clamp(ambient[1], 0.0f, 1.0f));
		Uint8 blue = static_cast<Uint8>(255 *
				std::clamp(ambient[2], 0.0f, 1.0f));
		return (red << 24 | green << 16 | blue << 8 | 0xFF);
	}

	float diff = fmax(dot(hit.normal, light_dir), 0.0f);
	float diffuse[3] = { _red * l->getRed() * diff,
						_green * l->getGreen() * diff,
						_blue * l->getBlue() * diff };

	Vec3 view_dir = (ray.dir * -1).normalize();
	Vec3 halfway = (light_dir + view_dir).normalize();
	float spec = powf(fmax(dot(hit.normal, halfway), 0.0f), _shininess);
	float specular[3] = { l->getRed() * spec,
						l->getGreen() * spec,
						l->getBlue() * spec };

	Uint8 red = static_cast<Uint8>(255 *
			std::clamp((ambient[0] + diffuse[0] + specular[0]), 0.0f, 1.0f));
	Uint8 green = static_cast<Uint8>(255 *
			std::clamp((ambient[1] + diffuse[1] + specular[1]), 0.0f, 1.0f));
	Uint8 blue = static_cast<Uint8>(255 *
			std::clamp((ambient[2] + diffuse[2] + specular[2]), 0.0f, 1.0f));

	return (red << 24 | green << 16 | blue << 8 | 0xFF);
}
