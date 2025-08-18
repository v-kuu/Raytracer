#pragma once
#include <vector>
#include <limits>
#include <memory>
#include "Texture.hpp"
#include "Camera.hpp"
#include "ALight.hpp"
#include "IMaterial.hpp"
#include "AHittable.hpp"
#include "HitRecord.hpp"
#include "BVHNode.hpp"
#include "ThreadPool.hpp"
#include "IMaterial.hpp"
#include "SkyboxMaterial.hpp"
#include "BlinnPhongMaterial.hpp"
#include "NormalMaterial.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "PointLight.hpp"

class	AHittable;
class	ALight;
class	Camera;
struct	BVHNode;

class	Scene
{
	public:
		Scene(void);
		~Scene(void) = default;
		Scene(const Scene &other) = delete;
		Scene	&operator=(const Scene &other) = delete;

		void	render(std::shared_ptr<Texture> target, ThreadPool &pool);

		std::shared_ptr<Camera>	getCam(void) const;
		const std::vector<std::unique_ptr<AHittable>>	&getObjects(void) const;
		const std::vector<std::shared_ptr<ALight>>		&getLights(void) const;
		const std::unique_ptr<BVHNode>					&getBVH(void) const;

	private:
		std::shared_ptr<Camera>						_cam;
		std::vector<std::unique_ptr<AHittable>>		_objects;
		std::vector<std::shared_ptr<ALight>>		_lights;
		std::unique_ptr<BVHNode>					_bvh;
};
