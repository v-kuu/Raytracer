#include "../inc/NormalMaterial.hpp"

Uint32	NormalMaterial::shade(const Ray &ray, const HitRecord &hit, const Scene &sc) const
{
	(void)ray;
	(void)sc;

	float	x = (hit.normal.x + 1.0f) * 0.5f;
	float	y = (hit.normal.y + 1.0f) * 0.5f;
	float	z = (hit.normal.z + 1.0f) * 0.5f;

	Uint8 red = static_cast<Uint8>(255.0f * x);
	Uint8 green = static_cast<Uint8>(255.0f * y);
	Uint8 blue = static_cast<Uint8>(255.0f * z);
	return (red << 24 | green << 16 | blue << 8 | 255);
}
