#pragma once
#include "IMaterial.hpp"

class	BlinnPhongMaterial : public IMaterial
{
	public:
		BlinnPhongMaterial(void) = delete;
		BlinnPhongMaterial(float r, float g, float b);
		~BlinnPhongMaterial(void) = default;
		BlinnPhongMaterial(const BlinnPhongMaterial &other);
		BlinnPhongMaterial	&operator=(const BlinnPhongMaterial &other);

		Uint32	shade(const Ray &ray, const AHittable::Hit &hit,
					const PointLight &l) override;

	private:
		static float	_shininess;

		float	_red;
		float	_green;
		float	_blue;
};
