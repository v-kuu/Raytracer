#pragma once
#include "IMaterial.hpp"
#include "AmbientLight.hpp"
#include "Scene.hpp"
#include "HitRecord.hpp"
#include "ITexture.hpp"
#include <algorithm>
#include <optional>

class	BlinnPhongMaterial : public IMaterial
{
	public:
		BlinnPhongMaterial(void) = delete;
		BlinnPhongMaterial(std::shared_ptr<ITexture> tex,
				float ref,
				std::optional<std::shared_ptr<ITexture>> normalMap = std::nullopt);
		~BlinnPhongMaterial(void) = default;
		BlinnPhongMaterial(const BlinnPhongMaterial &other);
		BlinnPhongMaterial &operator=(const BlinnPhongMaterial &other);

		Uint32 shade(const Ray &ray, const HitRecord &hit, const Scene &sc) const override;

	private:
		static float _shininess;
		static AmbientLight	_a;

		std::shared_ptr<ITexture> _texture;
		float _reflectivity;
		std::optional<std::shared_ptr<ITexture>> _normalMap;

		Vec3 _baseColor(const Ray &ray, const HitRecord &hit, const Scene &sc) const;
		Vec3 _reflectionColor(const Ray &ray, const HitRecord &hit, const Scene &sc) const;
		Uint32 _mixColor(const Vec3 &base, const Vec3 &refl) const;
		Vec3 _sampleNormalMap(const HitRecord &hit) const;
};
