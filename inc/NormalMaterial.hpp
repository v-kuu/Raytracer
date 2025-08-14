#pragma once
#include "IMaterial.hpp"

class	NormalMaterial : public IMaterial
{
	public:
		Uint32	shade(const Ray &ray, const HitRecord &hit, const Scene &sc) const override;
};
