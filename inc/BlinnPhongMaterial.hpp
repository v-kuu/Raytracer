#pragma once
#include "IMaterial.hpp"
#include "AmbientLight.hpp"
#include "Scene.hpp"
#include "HitRecord.hpp"
#include <algorithm>

class	BlinnPhongMaterial : public IMaterial
{
	public:
		BlinnPhongMaterial(void) = delete;
		BlinnPhongMaterial(float r, float g, float b, float ref);
		~BlinnPhongMaterial(void) = default;
		BlinnPhongMaterial(const BlinnPhongMaterial &other);
		BlinnPhongMaterial	&operator=(const BlinnPhongMaterial &other);

		Uint32	shade(const Ray &ray, const HitRecord &hit, const Scene &sc) const override;

	private:
		static float		_shininess;
		static AmbientLight	_a;

		float	_red;
		float	_green;
		float	_blue;
		float	_reflectivity;

		Uint32	_baseColor(const Ray &ray, const HitRecord &hit, const Scene &sc) const;
		Uint32	_reflectionColor(const Ray &ray, const HitRecord &hit, const Scene &sc) const;
		Uint32	_mixColor(Uint32 base, Uint32 refl) const;
};
