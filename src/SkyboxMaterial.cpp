#include "../inc/SkyboxMaterial.hpp"

Uint32	SkyboxMaterial::shade(const Ray &ray, const HitRecord &hit, const Scene &sc) const
{
	(void)hit;
	(void)sc;
	Vec3 unit_dir = ray.dir.normalize();
	float fraction = 0.5 * (-unit_dir.y + 1.0f);
	Uint8 red = (0xFF - 0x77) * fraction + (0x77);
	Uint8 green = (0xFF - 0xBB) * fraction + (0xBB);
	Uint8 blue = (0xFF - 0xFF) * fraction + (0xFF);
	return (red << 24 | green << 16 | blue << 8 | 0xFF);
}
