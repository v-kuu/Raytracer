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
		BlinnPhongMaterial(float r, float g, float b);
		~BlinnPhongMaterial(void) = default;
		BlinnPhongMaterial(const BlinnPhongMaterial &other);
		BlinnPhongMaterial	&operator=(const BlinnPhongMaterial &other);

		Uint32	shade(const Ray &ray, const HitRecord &hit, const Scene &sc) override;

	private:
		static float		_shininess;
		static AmbientLight	_a;

		float	_red;
		float	_green;
		float	_blue;
};
