#pragma once
#include "IMaterial.hpp"
#include "Scene.hpp"
#include "HitRecord.hpp"

class	Scene;
class	IMaterial;
struct	HitRecord;

class	SkyboxMaterial : public IMaterial
{
	public:
		Uint32	shade(const Ray &ray, const HitRecord &hit, const Scene &sc) const override;
};
